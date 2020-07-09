///
/// Created by Anonymous275 on 4/11/2020
///

#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

std::string FileList;
std::string FileSizes;
int ModsLoaded = 0;
long MaxModSize = 0;
void LuaMain(std::string Path);
void HandleResources(std::string path){
    struct stat info{};
    if(stat(path.c_str(), &info) != 0){
        fs::create_directory(path);
    }
    LuaMain(path);
    path += "/Client";
    if(stat(path.c_str(), &info) != 0) {
        fs::create_directory(path);
    }
    for (const auto & entry : fs::directory_iterator(path)){
        int pos = entry.path().string().find(".zip");
        if(pos != std::string::npos){
            if(entry.path().string().length() - pos == 4){
                FileList += entry.path().string() + ";";
                FileSizes += std::to_string(fs::file_size(entry.path()))+";";
                MaxModSize += fs::file_size(entry.path());
                ModsLoaded++;
            }
        }
    }
    std::replace(FileList.begin(),FileList.end(),'\\','/');
}