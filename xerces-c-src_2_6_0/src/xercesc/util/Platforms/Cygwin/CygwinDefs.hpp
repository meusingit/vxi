/*
 * Copyright 2004,2004 The Apache Software Foundation.
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
 * $Log: CygwinDefs.hpp,v $
 * Revision 1.2  2004/09/08 13:56:39  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.1  2004/02/17 15:56:50  neilg
 * fix for bug 25035; much thanks to Abe Backus
 *
 *
 */


// ---------------------------------------------------------------------------
//  NT and Win98 always run the CPU in little endian mode.
// ---------------------------------------------------------------------------
#define ENDIANMODE_LITTLE

typedef void* FileHandle;
