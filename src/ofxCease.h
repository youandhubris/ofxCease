#pragma once
#include "ofMain.h"

class ofxCease
{
    public:
    
        ofxCease(int year, int month, int day, int warningDays, string warningMessage, string alertMessage, string pathToRemove = "")
        {
            int daysLeft = GetTimeLeft(year, month, day) / 86400;
            
            if (daysLeft <= 0)
            {
                if (pathToRemove != "") Remove(pathToRemove);
                ofSystemAlertDialog(alertMessage);
                ofExit();
            }
            
            else if (daysLeft <= warningDays)
            {
                int p = warningMessage.find('#');
                warningMessage.replace(p, 1, ofToString(daysLeft));
                ofSystemAlertDialog(warningMessage);
            }
        }
    
        double GetTimeLeft(int year, int month, int day)
        {
            // Now, same as time_t now = time(nullptr);
            time_t now;
            time(&now);
            
            // Limit
            struct tm limitTM;
            limitTM = *localtime(&now);
            
            limitTM.tm_year = year - 1900;
            limitTM.tm_mon = month - 1;
            limitTM.tm_mday = day;
            
            time_t limit = mktime(&limitTM);
            ofLogNotice("ofxCease", "Now is " + ofToString(asctime(localtime(&now))) + "The limit is " + ofToString(asctime(localtime(&limit))));
            
            return difftime(mktime(&limitTM), now);
        }

        void Remove(string pathToRemove)
        {
#if defined( TARGET_OSX ) || defined( TARGET_LINUX )
            ofSystem("rm -rf " + pathToRemove);
            
#elif defined( TARGET_WIN32 )
            replace(pathToRemove.begin(), pathToRemove.end(), '/', '\\');
            ofSystem("DEL /Q " + pathToRemove);
            
#endif
            ofLogWarning("ofxCease", pathToRemove + " was removed.");
        }
};
