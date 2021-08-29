#include "utils/logger.h"
Logger::Logger(const Logger& ) {}
string currTime()
{
    char tmp[64];
    time_t ptime;
    time(&ptime);
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&ptime));
    return tmp;
}
Logger::Logger(){
    this->target = file_and_terminal;
    this->level = DEBUG;
    cout<<currTime()<<"[WELCOME]"<<" "<<"=== Start Logging ==="<<endl;
    string tmp = "";
    string welcome_dialog = tmp + "[WELCOME]" + ": " + currTime() + ":" + "=== Start Logging ===\n";
    if (target != terminal)
    {
        this->outfile.open(path);
        this->outfile << welcome_dialog;
        this->outfile.flush();
    }
}
Logger* Logger::instance = new Logger();
Logger *Logger::getInstance()
{ 
    return instance; 
}
    
Logger::Logger(log_target target, log_level level, string path)
{
    this->target = target;
    this->path=path;
    this->level=level;
    string tmp = "";
    string welcome_dialog = tmp +"[WELCOME]"+": "+currTime()+":"+"=== Start Logging ===\n";
    if(target != terminal)
    {
        this->outfile.open(path);
        this->outfile<<welcome_dialog;


    }
}
void Logger::output(string text,log_level act_level)
{
    string prefix;
    if(act_level == DEBUG) prefix = "[DEBUG]:   ";
    else if(act_level == INFO) prefix = "[INFO]:    ";
    else if(act_level==WARNING) prefix = "[WARNING]: ";
    else if(act_level==ERROR) prefix = "[ERROR]:   ";
    else if(act_level==FATAL) prefix = "[FATAL]:   ";
    else prefix = " ";
    prefix+="";
    string output_content=prefix+currTime()+":"+text+"\n";
    if((this->level>=DEBUG)&&(this->target!=terminal))
    {
    
        cout<<output_content;
        outfile<<output_content;
        outfile.flush();
    }
        


}
void Logger::debug(string text)
{
    this->output(text,DEBUG);
}
void Logger::info(string text)
{
    this->output(text,INFO);
}
void Logger::warning(string text)
{
    this->output(text,WARNING);
}
void Logger::error(string text)
{
    this->output(text, ERROR);
}
void Logger::fatal(string text)
{
    this->output(text,FATAL);
}
