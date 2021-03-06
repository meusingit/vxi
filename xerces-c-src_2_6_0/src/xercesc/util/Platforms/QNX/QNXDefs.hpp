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
 * $Log: QNXDefs.hpp,v $
 * Revision 1.2  2004/09/08 13:56:42  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.1  2003/03/13 22:11:16  tng
 * [Bug 17858] Support for QNX/Neutrino.  Patch from Chris McKillop.
 *
 */


// ---------------------------------------------------------------------------
//  Detect endian mode
// ---------------------------------------------------------------------------
#include <gulliver.h>

#if defined(__LITTLEENDIAN__)
  #define ENDIANMODE_LITTLE
#elif defined(__BIGENDIAN__)
  #define ENDIANMODE_BIG
#else
  #error: unknown byte order!
#endif 

#include <stdio.h>
typedef FILE* FileHandle;

