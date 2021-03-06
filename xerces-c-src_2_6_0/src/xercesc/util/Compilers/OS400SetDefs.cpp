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
 * $Log: OS400SetDefs.cpp,v $
 * Revision 1.2  2004/09/08 13:56:32  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.1.1.1  2002/02/01 22:22:18  peiyongz
 * sane_include
 *
 * Revision 1.3  2000/03/02 19:55:08  roddey
 * This checkin includes many changes done while waiting for the
 * 1.1.0 code to be finished. I can't list them all here, but a list is
 * available elsewhere.
 *
 * Revision 1.2  2000/02/06 07:48:18  rahulj
 * Year 2K copyright swat.
 *
 */

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------

#include <sys/types.h>
#include <ctype.h>
 int
strcasecmp (const char *string1,const char * string2)
 {
  char *s1, *s2;
  int result;

  s1 = (char *)string1;
  s2 = (char *)string2;

  while ((result = tolower (*s1) - tolower (*s2)) == 0)
    {
      if (*s1++ == '\0')
        return 0;
      s2++;
    }
  return (result);
}
int
strncasecmp (const char *string1,const char *string2,size_t count)
{
  register char *s1, *s2;
  register int r;
  register unsigned int rcount;
  rcount = (unsigned int) count; 
  if (rcount > 0)
    {
      s1 = (char *)string1;
      s2 = (char *)string2;
      do
	{
	  if ((r = tolower (*s1) - tolower (*s2)) != 0)
	    return r;
	  if (*s1++ == '\0')
	    break;
	  s2++;
	}
      while (--rcount != 0);
    }
  return (0);
}
/* des not appear as though the following is needed */
#ifndef __OS400__
int stricmp(const char* str1, const char*  str2)
{
 return strcasecmp(str1, str2);
}

int strnicmp(const char* str1, const char* str2, const unsigned int count)
{
	if (count == 0)
		return 0;

	return strncasecmp( str1, str2, (size_t)count);
}
#endif
