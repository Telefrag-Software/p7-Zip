// MainAr.cpp

#include "StdAfx.h"

// #include <locale.h>

#include "Windows/COM.h"
#include "Windows/Error.h"

#include "Common/StdOutStream.h"
#include "Common/NewHandler.h"
#include "Common/StringConvert.h"

#include "ConsoleClose.h"
#include "ArError.h"

using namespace NWindows;

// extern int Main2(int numArguments, const char *arguments[]);
extern int Main2();

static const char *kExceptionErrorMessage = "\n\nError:\n";
static const char *kUserBreak  = "\nBreak signaled\n";

static const char *kMemoryExceptionMessage = "\n\nMemory Error! Can't allocate!\n";
static const char *kUnknownExceptionMessage = "\n\nUnknown Error\n";
static const char *kInternalExceptionMessage = "\n\nInternal Error #";

int main(int numArguments, const char *arguments[])
{
   myInit(numArguments,arguments); // FIXED


  int result=1;
#ifdef WIN32  
  NCOM::CComInitializer comInitializer;
#endif
  try
  {
    NConsoleClose::CCtrlHandlerSetter aCtrlHandlerSetter;
    try
    {
      // result = Main2(numArguments, arguments);
      result = Main2();
    }
    catch(const NConsoleClose::CCtrlBreakException &)
    {
      g_StdOut << endl << kUserBreak;
      return (NExitCode::kUserBreak);
    }
  }
  catch(const CNewException)
  {
    g_StdOut << kMemoryExceptionMessage;
    return (NExitCode::kMemoryError);
  }
  catch(const CSystemException &e)
  {
    g_StdOut << "System Error: " << (UINT64)(e.ErrorCode);
    return (NExitCode::kFatalError);
  }
  catch(NExitCode::EEnum &aExitCode)
  {
    g_StdOut << kInternalExceptionMessage << aExitCode << endl;
    return (aExitCode);
  }
  catch(const NExitCode::CSystemError &systemError)
  {
    UString message;
    NError::MyFormatMessage(systemError.ErrorValue, message);
    g_StdOut << endl << endl << "System error:" << endl << 
        message << endl;
    return (NExitCode::kFatalError);
  }
  catch(const NExitCode::CMultipleErrors &multipleErrors)
  {
    g_StdOut << endl << multipleErrors.NumErrors << " errors" << endl;
    return (NExitCode::kFatalError);
  }
  catch(const UString &s)
  {
    g_StdOut << kExceptionErrorMessage << s << endl;
    return (NExitCode::kFatalError);
  }
  catch(const char *s)
  {
    g_StdOut << kExceptionErrorMessage << s << endl;
    return (NExitCode::kFatalError);
  }
  catch(int t)
  {
    g_StdOut << kInternalExceptionMessage << t << endl;
    return (NExitCode::kFatalError);
  }
  catch(...)
  {
    g_StdOut << kUnknownExceptionMessage;
    return (NExitCode::kFatalError);
  }
  return result;
}
