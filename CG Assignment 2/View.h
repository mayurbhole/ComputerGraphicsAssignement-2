#ifndef VIEW_H_INCLUDED
#define VIEW_H_INCLUDED

#include "ReadPlyFile.h"

class View
{
    private:
            ReadPlyFile readObj;
                //Spotlight
    //    int spin = 0;
     //   int lightSubFlag=2;


    public:
            static int lightFlag;
            static int lightSubFlag;
            static int spin;

            View();
            void initLighting();
            void dispCallBack();
            void setupDisplayCallBack();

};





#endif // VIEW_H_INCLUDED
