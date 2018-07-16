/**
 * Copyright (c) 2017 Baidu.com, Inc. All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
 * an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License.
 *
 * @author baidu aip
 */
#ifndef __AIP_UTILS_H__
#define __AIP_UTILS_H__

#include <string>
#include <fstream>
#include <ctype.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <algorithm>
#include <openssl/md5.h>

#include <map>
#include <sstream>
#include <fstream>

const int __BCE_VERSION__ = 1;
const int __BCE_EXPIRE__ = 1800;

namespace aip {

    template<class CharT, class Traits, class Allocator>
    std::basic_istream<CharT, Traits>& getall(std::basic_istream<CharT, Traits>& input,
                                              std::basic_string<CharT, Traits, Allocator>& str) {
        std::ostringstream oss;
        oss << input.rdbuf();
        str.assign(oss.str());
        return input;
    }

    inline int get_file_content(const char *filename, std::string* out) {
        std::ifstream in(filename, std::ios::in | std::ios::binary);
        if (in) {
            getall(in, *out);
            return 0;
        } else {
            return -1;
        }
    }

    inline std::string to_upper(std::string src)
    {
        std::transform(src.begin(), src.end(), src.begin(), toupper);
        return src;
    }


    inline std::string to_lower(std::string src)
    {
        std::transform(src.begin(), src.end(), src.begin(), tolower);
        return src;
    }

    inline std::string to_hex(unsigned char c, bool lower = false)
    {
        const std::string hex = "0123456789ABCDEF";

        std::stringstream ss;
        ss << hex[c >> 4] << hex[c & 0xf];

        return lower ? to_lower(ss.str()) : ss.str();
    }

    inline time_t now()
    {
        return time(NULL);
    }

    std::string utc_time(time_t timestamp);

    void url_parse(
            const std::string & url,
            std::map<std::string, std::string> & params);

    std::string url_encode(const std::string & input, bool encode_slash = true);
    std::string canonicalize_params(std::map<std::string, std::string> & params);

    std::string canonicalize_headers(std::map<std::string, std::string> & headers);

    std::string get_headers_keys(std::map<std::string, std::string> & headers);

    std::string get_host(const std::string & url);

    std::string get_path(const std::string & url);

    std::string hmac_sha256(
            const std::string & src,
            const std::string & sk);

    void sign(
            std::string method,
            std::string & url,
            std::map<std::string, std::string> & params,
            std::map<std::string, std::string> & headers,
            std::string & ak,
            std::string & sk);

}

#endif
