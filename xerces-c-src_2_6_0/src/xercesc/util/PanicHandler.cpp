/*
 * Copyright 2003,2004 The Apache Software Foundation.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * $Id: PanicHandler.cpp,v 1.2 2004/09/08 13:56:22 peiyongz Exp $
 * $Log: PanicHandler.cpp,v $
 * Revision 1.2  2004/09/08 13:56:22  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.1  2003/03/09 17:06:16  peiyongz
 * PanicHandler
 *
 *
 */


// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/util/PanicHandler.hpp>

XERCES_CPP_NAMESPACE_BEGIN

const char* PanicHandler::getPanicReasonString(const PanicReasons reason)
{
    const char* reasonStr;

    switch (reason)
    {
    case Panic_NoTransService:
        reasonStr = "Could not load a transcoding service";
        break;
    case Panic_NoDefTranscoder:
        reasonStr = "Could not load a local code page transcoder";
        break;
    case Panic_CantFindLib:
        reasonStr = "Could not find the xerces-c DLL";
        break;
    case Panic_UnknownMsgDomain:
        reasonStr = "Unknown message domain";
        break;
    case Panic_CantLoadMsgDomain:
        reasonStr = "Cannot load message domain";
        break;
    case Panic_SynchronizationErr:
        reasonStr = "Cannot synchronize system or mutex";
        break;
    case Panic_SystemInit:
        reasonStr = "Cannot initialize the system or mutex";
        break;
    default:
        reasonStr = "Unknown reason";
        break;
    }	

    return reasonStr;

}

XERCES_CPP_NAMESPACE_END

