#include "TerminalEmulator.h"
#include <wx/filename.h>
#include <wx/log.h>
#include "processreaderthread.h"
#include "macros.h"

#ifndef __WXMSW__
#include <signal.h>
#endif

wxDEFINE_EVENT(wxEVT_TERMINAL_COMMAND_EXIT, clCommandEvent);
wxDEFINE_EVENT(wxEVT_TERMINAL_COMMAND_OUTPUT, clCommandEvent);

TerminalEmulator::TerminalEmulator()
    : m_process(NULL)
{
    Bind(wxEVT_ASYNC_PROCESS_OUTPUT, &TerminalEmulator::OnProcessOutput, this);
    Bind(wxEVT_ASYNC_PROCESS_TERMINATED, &TerminalEmulator::OnProcessTerminated, this);
}

TerminalEmulator::~TerminalEmulator() {}

bool TerminalEmulator::ExecuteConsole(const wxString& command,
                                      const wxString& workingDirectory,
                                      bool waitOnExit,
                                      const wxString& title)
{
    wxString consoleCommand;
    wxString strTitle = title;
    if(strTitle.IsEmpty()) {
        strTitle << "'" << command << "'";
    } else {
        strTitle.Prepend("'").Append("'");
    }

#ifdef __WXMSW__
    consoleCommand = PrepareCommand(command, strTitle, waitOnExit);

#elif defined(__WXGTK__)
    // Test for the common terminals on Linux
    if(wxFileName::Exists("/usr/bin/gnome-terminal")) {
        consoleCommand << "/usr/bin/gnome-terminal -t " << strTitle << " -x "
                       << PrepareCommand(command, strTitle, waitOnExit);

    } else if(wxFileName::Exists("/usr/bin/konsole")) {
        consoleCommand << "/usr/bin/konsole -e " << PrepareCommand(command, strTitle, waitOnExit);

    } else if(wxFileName::Exists("/usr/bin/lxterminal")) {
        consoleCommand << "/usr/bin/lxterminal -T " << strTitle << " -e " << PrepareCommand(command, strTitle, waitOnExit);

    } else if(wxFileName::Exists("/usr/bin/uxterm")) {
        consoleCommand << "/usr/bin/uxterm -T " << strTitle << " -e " << PrepareCommand(command, strTitle, waitOnExit);

    } else if(wxFileName::Exists("/usr/bin/xterm")) {
        consoleCommand << "/usr/bin/xterm -T " << strTitle << " -e " << PrepareCommand(command, strTitle, waitOnExit);
    }

#elif defined(__WXMAC__)
    
    wxString consoleCommand = TERMINAL_CMD;
    consoleCommand.Replace("$(CMD)", command);
    wxUnusedVar(strTitle);
    wxUnusedVar(waitOnExit);
    
#endif
    if(consoleCommand.IsEmpty()) return false;
    wxLogMessage(consoleCommand);
    
    return ::wxExecute(consoleCommand) != 0;
}

wxString TerminalEmulator::PrepareCommand(const wxString& str, const wxString& title, bool waitOnExit)
{
    wxString command;
#ifdef __WXGTK__
    // First escape any double quotes
    // so "Some Command" -> \"Some Command\"
    wxString escapedString = str;
    escapedString.Replace("\"", "\\\"");
    command << "/bin/bash -c \"" << escapedString;
    if(waitOnExit) {
        command << " && echo 'Hit ENTER to continue' && read";
    }
    command << "\"";

#elif defined(__WXMSW__)
    // Windows
    wxString escapedString = str;
    command << "cmd /c call title " << title << " && " << escapedString;
    if(waitOnExit) {
        command << " && echo \"\" && pause";
    }
#else
// OSX

#endif
    return command;
}

void TerminalEmulator::OnProcessTerminated(clProcessEvent& event)
{
    // Process terminated
    wxDELETE(m_process);

    // Notify that the terminal has terminated
    clCommandEvent terminateEvent(wxEVT_TERMINAL_COMMAND_EXIT);
    AddPendingEvent(terminateEvent);
}

void TerminalEmulator::Terminate()
{
    if(IsRunning()) {
        m_process->Terminate();
    }
}

bool TerminalEmulator::IsRunning() const { return m_process != NULL; }

void TerminalEmulator::OnProcessOutput(clProcessEvent& event)
{
    clCommandEvent evtOutput(wxEVT_TERMINAL_COMMAND_OUTPUT);
    evtOutput.SetString(event.GetOutput());
    AddPendingEvent(evtOutput);
}

bool TerminalEmulator::ExecuteNoConsole(const wxString& commandToRun, const wxString& workingDirectory)
{
    if(m_process) {
        // another process is running
        return false;
    }

    wxString command;
#ifdef __WXMSW__
    wxString shell = wxGetenv("COMSPEC");
    if(shell.IsEmpty()) {
        shell = "CMD";
    }

    command << shell << wxT(" /c \"");
    command << commandToRun << wxT("\"");

#else
    wxString tmpCmd = commandToRun;
    command << "/bin/sh -c '";
    // escape any single quoutes
    tmpCmd.Replace("'", "\\'");
    command << tmpCmd << "'";
#endif
    wxLogMessage("TerminalEmulator::ExecuteNoConsole: %s", command);
    m_process = ::CreateAsyncProcess(this, command, IProcessCreateWithHiddenConsole, workingDirectory);
    return m_process != NULL;
}
