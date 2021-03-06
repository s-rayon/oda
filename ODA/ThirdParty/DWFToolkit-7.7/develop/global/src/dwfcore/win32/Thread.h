//
//  Copyright (c) 2003-2006 by Autodesk, Inc.
//
//  By using this code, you are agreeing to the terms and conditions of
//  the License Agreement included in the documentation for this code.
//
//  AUTODESK MAKES NO WARRANTIES, EXPRESS OR IMPLIED,
//  AS TO THE CORRECTNESS OF THIS CODE OR ANY DERIVATIVE
//  WORKS WHICH INCORPORATE IT.
//
//  AUTODESK PROVIDES THE CODE ON AN "AS-IS" BASIS
//  AND EXPLICITLY DISCLAIMS ANY LIABILITY, INCLUDING
//  CONSEQUENTIAL AND INCIDENTAL DAMAGES FOR ERRORS,
//  OMISSIONS, AND OTHER PROBLEMS IN THE CODE.
//
//  Use, duplication, or disclosure by the U.S. Government is subject to
//  restrictions set forth in FAR 52.227-19 (Commercial Computer Software
//  Restricted Rights) and DFAR 252.227-7013(c)(1)(ii) (Rights in Technical
//  Data and Computer Software), as applicable.
//

#ifndef _DWFCORE_THREAD_WIN32_H
#define _DWFCORE_THREAD_WIN32_H

///
///\file        dwfcore/win32/Thread.h
///\brief       This header contains the DWFThread class declaration for Microsoft Windows platforms.
///
///\warning     This file should never be included directly.  
///             Instead, include \a dwfcore/Synchronization.h and all 
///             related header files, appropriate with the build configuration,
///             will be included.
///
///\todo        Change to a non-final implementation pattern where DWFCore::DWFThread is declared in a common header file.  
///             These generic classes will then use a platform-specific
///             implementation object to deliver the required functional behavior.  
///


#include "dwfcore/Core.h"

#ifdef  _DWFCORE_WIN32_SYSTEM

#ifndef _DWFCORE_SYNCHRONIZATION_H
#error  This header should not be included directly - use "dwfcore/Synchronization.h" instead
#endif


namespace DWFCore
{

//
// fwd decl
//
class DWFThreadWorker;
class DWFThreadPool;


///
///\class           DWFThread   dwfcore/win32/Thread.h  "dwfcore/win32/Thread.h"
///\brief           A pooled worker thread implementation for Microsoft Windows platforms.
///\since           1.0.1
///
///\ingroup         CrossPlatformInterface
///
class DWFThread : virtual public DWFCoreMemory
{

public:

    ///
    ///\enum    teState
    ///\brief   Enumeration values that define the thread state.
    ///
    ///         The thread is created in the \a eNone state and 
    ///         switches to \a eRun when \a run() is invoked;
    ///         the final state is \a eEnd.
    ///         
    ///         If the thread is suspended the current state
    ///         is cached and the state is changed to \a eSuspend.  
    ///         If resumed, the state is restored to its previous value unless
    ///         a state change was made during the suspension.
    ///
    typedef enum
    {
        ///
        ///     Indicates the thread is not executing in the thread pool;
        ///     the thread has not yet entered the \a run() method.
        ///
        eNone,

        ///
        ///     Indicates the thread is executing in the thread pool;
        ///     the thread is inside of the \a run() method.
        ///
        eRun,

        ///
        ///     Indicates the thread is no longer executing the thread pool;
        ///     the thread has exited the \a run() method.
        ///
        eEnd,

        ///
        ///     Currently only used internally for state change requests to forcibly terminate execution.
        ///
        eKill,

        ///
        ///     Indicates the thread executing in the thread pool has been suspended;
        ///     the thread is inside of the \a run() method.
        ///     This value is also used internally for state change requests.
        ///
        eSuspend

    } teState;

public:

    ///
    ///         Destructor
    ///
    ///\throw   None
    ///
    ~DWFThread()
        throw();

    ///
    ///         Runs the main thread logic.  This method is invoked
    ///         within the thread function by the thread pool.
    ///
    ///\throw   None
    ///
    void run()
        throw();

    ///
    ///         Requests the thread end normally.
    ///
    ///\throw   DWFException
    ///
    void end()
        ;

    ///
    ///         Request the thread terminate immediately.
    ///
    ///\throw   DWFException
    ///
    void kill()
        ;

    ///
    ///         Request the thread suspended itself.
    ///
    ///\throw   DWFException
    ///
    void suspend()
        ;

    ///
    ///         Request the suspended thread resume itself.
    ///
    ///\throw   DWFException
    ///
    void resume()
        ;

private:
    friend class DWFThreadPool;

    //
    // Constructor
    //
    DWFThread( DWFThreadPool& rPool )
        throw();

    //
    // Begins the thread
    //
    void _begin()
        ;

    //
    // Joins the thread
    //
    void _join()
        ;

    //
    // Runs a worker in the thread
    //
    void _work( DWFThreadWorker& rWorker )
        ;

    //
    // returns the current run state
    //
    teState _state()
        ;

    //
    // sets the current run state
    //
    void _setstate( teState eState )
        ;

    //
    // returns the current state change request
    //
    teState _requeststate()
        ;

    //
    // requests a state change
    //
    void _setrequest( teState eState )
        ;

private:

    DWFThreadPool&      _rPool;

    HANDLE              _hThread;
    CRITICAL_SECTION    _oStateLock;

    DWFSignal           _oWorkSignal;
    DWFThreadWorker*    _pWorker;

    volatile teState    _eRunState;
    volatile teState    _eRequestState;
    volatile teState    _eLastSuspendedState;

private:

    //
    // Not Implemented
    //
    DWFThread( const DWFThread& );
    DWFThread& operator=( const DWFThread& );
};

}



#else
#error  This is a Win32 header file and is incompatible with your current system configuration
#endif 

#endif


