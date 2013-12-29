/*
* Copyright 2013 the original author or authors.
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

//include <dragon/io/native/${platform}/FileInputStream.cc>

#include <dragon/io/FileOutputStream.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <stdio.h>

Import dragon::io;

FileOutputStream::FileOutputStream(const Char* name)  throw(FileNotFoundException) {
    baseFile = new File(name);

    if(_wsopen_s(&mhFile,baseFile->getCanonicalPath(),_O_BINARY|_O_WRONLY,_SH_DENYNO,0)!=0)
    {
        throw FileNotFoundException();
    }
}

FileOutputStream::FileOutputStream(const Char* name,bool append)  throw(FileNotFoundException)
{
    baseFile=new File(name);

    int oflag=_O_BINARY|_O_WRONLY;
    if(append) oflag=_O_BINARY|_O_WRONLY|_O_APPEND;

    if(_wsopen_s(&mhFile,baseFile->getCanonicalPath(),oflag,_SH_DENYNO,0)!=0)
    {
        throw FileNotFoundException();
    }
}

FileOutputStream::FileOutputStream(File* file) throw(FileNotFoundException)
{
    baseFile=file;

    if(_wsopen_s(&mhFile,baseFile->getCanonicalPath(),_O_BINARY|_O_WRONLY,_SH_DENYNO,0)!=0)
    {
        throw FileNotFoundException();
    }
}

FileOutputStream::FileOutputStream(File* file, bool append) throw(FileNotFoundException)
{
    baseFile=file;

    int oflag=_O_BINARY|_O_WRONLY;
    if(append) oflag=_O_BINARY|_O_WRONLY|_O_APPEND;

    if(_wsopen_s(&mhFile,baseFile->getCanonicalPath(),oflag,_SH_DENYNO,0)!=0)
    {
        throw FileNotFoundException();
    }
}

void FileOutputStream::write(int b) throw(IOException)
{
    byte tb=(byte)b;

    if(_write(mhFile,&tb,1)==-1)
    {
        throw IOException();
    }
}

void FileOutputStream::close() throw(IOException)
{
    if(mhFile!=0)
    {
        if(_close(mhFile)==-1)
        {
            throw IOException();
        }

        mhFile=0;
    }
}

void FileOutputStream::flush() throw(IOException)
{
    if(_commit(mhFile))
    {
        throw IOException();
    }
}


void FileOutputStream::write(byte* b,int num) 
        throw(IOException,NullPointerException)
{
    if(b==null)
    {
        throw NullPointerException();
    }

    if(_write(mhFile,b,num)==-1)
    {
        throw IOException();
    }
}

void FileOutputStream::write(byte* b,int num,int off,int len) 
        throw(IOException,NullPointerException,IndexOutOfBoundsException)
{
    if(b==null)
    {
        throw NullPointerException();
    }

    if(off<0 || len<0 || off+len>num)
    {
        throw IndexOutOfBoundsException();
    }

    if(_write(mhFile,b+off,len)==-1)
    {
        throw IOException();
    }
}