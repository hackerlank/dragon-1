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


#include <dragonx/imageio/BufferedImage.h>

Import dragonx::imageio;

const Type* BufferedImage::TYPE = TypeOf<BufferedImage>();

BufferedImage::BufferedImage(int width, int height, const ColorModel* colorModel) 
    :width(width), height(height) {
    this->colorModel = new ColorModel(colorModel);

    int total = this->size();
    this->data = (byte*)malloc(total);
}

BufferedImage::~BufferedImage() {
    SafeDelete(this->colorModel);
    SafeFree(this->data);
}

int BufferedImage::getWidth() const {
    return this->width;
}

int BufferedImage::getHeight() const {
    return this->height;
}

const byte* BufferedImage::getRawData() const {
    return this->data;
}

int BufferedImage::size() const {
    return this->width * this->height * this->colorModel->getBitCount();
}
const Array<byte> BufferedImage::getData() const {
    return Array<byte>(this->data, this->size());
}