/*
 * Copyright 1999-2000,2004 The Apache Software Foundation.
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
 * $Log: OS2Defs.hpp,v $
 * Revision 1.2  2004/09/08 13:56:41  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.1.1.1  2002/02/01 22:22:25  peiyongz
 * sane_include
 *
 * Revision 1.3  2000/03/02 19:55:27  roddey
 * This checkin includes many changes done while waiting for the
 * 1.1.0 code to be finished. I can't list them all here, but a list is
 * available elsewhere.
 *
 * Revision 1.2  2000/02/06 07:48:29  rahulj
 * Year 2K copyright swat.
 *
 * Revision 1.1.1.1  1999/11/09 01:06:42  twl
 * Initial checkin
 *
 * Revision 1.2  1999/11/08 20:45:31  rahul
 * Swat for adding in Product name and CVS comment log variable.
 *
 */


// ---------------------------------------------------------------------------
//  OS2 always run the CPU in little endian mode.
// ---------------------------------------------------------------------------
#define ENDIANMODE_LITTLE


// ---------------------------------------------------------------------------
//  Define all the required platform types
// ---------------------------------------------------------------------------
typedef void*   FileHandle;
