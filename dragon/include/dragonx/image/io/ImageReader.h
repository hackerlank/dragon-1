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
 * Created:     2013/12/29
 **********************************************************************/


#ifndef ImageReader_Image_IO_Dragonx_H
#define ImageReader_Image_IO_Dragonx_H

#include <dragon/config.h>

#include <dragon/io/InputStream.h>
#include <dragon/io/IOException.h>

#include <dragonx/image/BufferedImage.h>

BeginPackage3(dragonx, image, io)

Import dragon::io;
Import dragonx::image;

interface_ ImageReader {
public:
    virtual ~ImageReader(){};

public:
    virtual BufferedImage* read(InputStream* input) 
        throw(IOException*) = 0;

};//ImageReader

EndPackage3 //(dragonx, image, io)

#endif //ImageReader_Image_IO_Dragonx_H
