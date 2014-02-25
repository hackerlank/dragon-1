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

/**********************************************************************
 * Author:      Owen Wu/wcw/yubing
 * Email:       yubing744@163.com
 * Created:     2014/02/23
 **********************************************************************/


#ifndef AbstractAudioInputStream_Plugins_Io_Audio_Dragonx_H
#define AbstractAudioInputStream_Plugins_Io_Audio_Dragonx_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <dragon/io/InputStream.h>
#include <dragonx/audio/io/AudioInputStream.h>

BeginPackage4(dragonx, audio, io, plugins)

Import dragon::io;
Import dragon::lang;

class_ AbstractAudioInputStream extends(AudioInputStream) {
public:
    static const Type* TYPE;
    
public:
    AbstractAudioInputStream(const InputStream* stream);
    virtual ~AbstractAudioInputStream();

public:
    virtual wlong_u skip(wlong_u n) throw(IOException*);
    virtual const AudioFormat* getFormat() const;
    virtual void checkReadSize(int size) throw(IOException*);

public:
    virtual void open() = 0;
    virtual int read(byte* b, int num, int off, int len) throw(IOException*) = 0;
    virtual void close() throw(IOException*) = 0;

protected:
    InputStream* stream;
    AudioFormat* format;
    void* nativeData;
};//AbstractAudioInputStream

EndPackage4 //(dragonx, audio, io, plugins)

#endif //AbstractAudioInputStream_Plugins_Io_Audio_Dragonx_H
