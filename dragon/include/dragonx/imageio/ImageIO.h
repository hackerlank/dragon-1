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
 * Created:     2013/12/28
 **********************************************************************/


#ifndef ImageIO_Imageio_Dragonx_H
#define ImageIO_Imageio_Dragonx_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>

#include <dragon/io/InputStream.h>
#include <dragon/io/OutputStream.h>

#include <dragon/io/IOException.h>

#include <dragonx/imageio/BufferedImage.h>
#include <dragonx/imageio/RenderedImage.h>
#include <dragonx/imageio/spi/ImageIORegistry.h>

BeginPackage2(dragonx, imageio)

Import dragon::io;
Import dragon::lang;
Import dragonx::imageio::spi;


class_ ImageIO extends(Object) {
public:
    static const Type* TYPE;
    static ImageIORegistry* theRegistry;

public:
    static BufferedImage* read(const InputStream* input, const String& formatType) throw(IOException*);
    static void write(const RenderedImage* image, const String& formatType, const OutputStream* output) throw(IOException*);

public:
    ImageIO();
    virtual ~ImageIO();

};//ImageIO

EndPackage2 //(dragonx, imageio)

#endif //ImageIO_Imageio_Dragonx_H