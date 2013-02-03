#ifndef COMMUNICATIONINTERFACE_H
#define COMMUNICATIONINTERFACE_H

#pragma pack ( push, CommunicationInterface )

//Finds the Map Point application if installed on the computer
#import "progid:MapPoint.Application" \
no_implementation rename("EOF", "MP_EOF")

#pragma pack ( pop, CommunicationInterface )

#endif