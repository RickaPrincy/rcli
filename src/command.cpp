#include <RCli/Command.hpp>

using namespace RCli;

Command::Command(String name, String description, Callback callback){
    _name = _name;
    _description = _description;
    _callback = callback;
}

String Command::get_name(){
    return _name;
}

String Command::get_description(){
    return _description;
}

bool Command::matched(String text){
    return _name == text;
}

bool Command::call_if_matched(String text){
    if(matched(text)){
        _callback();
        return true;
    }
    return false;
}

void Command::print_help(){
    
}