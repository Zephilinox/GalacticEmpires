/*
 * Copyright (c) 2014 Jake Horsfield
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef INI_PARSER_H
#define INI_PARSER_H

#include <map>
#include <string>
#include <vector>
#include <utility>

class ini_parser
{
    public:
        ini_parser(const std::string& filename);

        int get_int(const std::string& name, const std::string& section = "") const;
        bool get_bool(const std::string& name, const std::string& section = "") const;
        long get_long(const std::string& name, const std::string& section = "") const;
        float get_float(const std::string& name, const std::string& section = "") const;
        double get_double(const std::string& name, const std::string& section = "") const;
        std::string get_string(const std::string& name, const std::string& section = "") const;

        void set_value(const std::string& name, int value, const std::string& section = "");
        void set_value(const std::string& name, bool value, const std::string& section = "");
        void set_value(const std::string& name, long value, const std::string& section = "");
        void set_value(const std::string& name, float value, const std::string& section = "");
        void set_value(const std::string& name, double value, const std::string& section = "");
        void set_value(const std::string& name, const std::string& value, const std::string& section = "");

    private:
        void parse(const std::string& filename);

        void start_section(const std::string& line);
        std::string extract_section_name(const std::string& line) const;

        void handle_assignment(const std::string& line);
        std::string extract_key(const std::string& line) const;
        std::string extract_value(const std::string& value) const;

        bool is_comment_line(const std::string& line) const;
        bool is_section_start_line(const std::string& line) const;
        bool is_assignment_line(const std::string& line) const;

        void ensure_property_exists(const std::string& section, const std::string& name) const;

    private:
        const std::string filename;
        std::vector<std::string> input;

        typedef std::map<std::string, std::string> properties;
        std::map<std::string, properties> sections;

        std::string current_section;

        static const std::string BOOL_TRUE;
        static const std::string BOOL_FALSE;
};

#endif
