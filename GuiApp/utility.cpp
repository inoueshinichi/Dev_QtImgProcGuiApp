/**
 * @file utility.cpp
 * @author inoue shinichi (inoue.shinichi.1800@gmail.com)
 * @brief GuiAppプロジェクトにおける自作関数用Sourceファイル
 * @version 0.1
 * @date 2021-08-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "utility.h"

#include <IsCommon/format_string.hpp>



std::string getNewSerialNoFilename(const std::string &filename,
                                   const std::set<std::string> &filenameSet)
{
    /* 最新の連番付きファイル名を取得する.
       連番の付け方: name(-番号).拡張子
       ※番号の最大値+1を新たな番号とするので, 途中歯抜けになっている番号は無視する.
    */
    std::string pattern = R"(^.+\..+$)"; // 拡張子の有無
    std::regex re0(pattern);
    std::smatch match;
    if (std::regex_match(filename, match, re0))
    {
        // 拡張子付きの場合

        if (!filenameSet.contains(filename))
        {
            return filename;
        }

        std::string name;
        std::string ext;
        pattern = R"(^(.+)-([0-9]+)\.(.+)$)";
        std::regex re1(pattern);
        int no = -1;
        if (std::regex_match(filename, match, re1))
        {
            // 連番付き
            name = match[1];
            no = std::stoi(match[2]);
            ext = match[3];
        }
        else
        {
            auto pos = filename.rfind('.');
            if (pos != std::string::npos)
            {
                name = filename.substr(0, pos); // Head
                ext = filename.substr(pos + 1); // Tail
            }
            else
            {
                return std::string();
            }
        }

        // filenameSetにあるファイル名を検索
        pattern = is::common::format_string(R"(^(%s-[0-9]+|(%s-%d-[0-9]+))\.(%s)$)", 
                                name.c_str(), name.c_str(), no, ext.c_str());
        std::regex re2(pattern);
        int count = 0;
        int subCount = 0;
        bool isDoubleCount = false;
        for (auto iter = filenameSet.begin(); iter != filenameSet.end(); ++iter)
        {
            if (std::regex_match(*iter, match, re2))
            {
                count++;
                if (filename == match[0])
                    isDoubleCount = true;
                std::string nameWithIndex = match[2];
                if (!nameWithIndex.empty())
                {
                    subCount++;
                }
            }
        }

        std::string newFilename;
        if (isDoubleCount)
        {
            newFilename = is::common::format_string("%s-%d-%d.%s", name.c_str(), no, subCount, ext.c_str());
        }
        else
        {
            newFilename = is::common::format_string("%s-%d.%s", name.c_str(), count - subCount, ext.c_str());
        }

        return newFilename;
    }
    else
    {
        return std::string();
    }
}