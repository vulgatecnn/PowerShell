//! @file test-getfullyqualifiedname.cpp
//! @author George Fleming <v-geflem@microsoft.com>
//! @brief Unit tests for GetFullyQualifiedName

#include <gtest/gtest.h>
#include "getcomputername.h"
#include "getfullyqualifiedname.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>

TEST(GetFullyQualifiedNameTest, ValidateLinuxGetFullyQualifiedDomainName)
{
    std::string actual(GetFullyQualifiedName());
    std::string hostname(GetComputerName());

    struct addrinfo hints, *info;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_CANONNAME;
    EXPECT_FALSE(getaddrinfo(hostname.c_str(), "http", &hints, &info));

    // Compare canonical name to FQDN
    //EXPECT_STREQ(info->ai_canonname, actual.c_str());
        char *info_a,*info_b;
    info_a=(char *)malloc(sizeof(info->ai_canonname));
    info_b=(char *)malloc(sizeof(actual.c_str()));
    int i=0;
    while(*(info->ai_canonname+i)!='\0'){

        if(*(info->ai_canonname+i)<='Z' && ((*(info->ai_canonname+i)>='A')))
            info_a[i]=*(info->ai_canonname+i)+'a'-'A';
        else
            info_a[i]=*(info->ai_canonname+i);
        i++;
    }
    info_a[i]='\0';
    i=0;
    while(*(actual.c_str()+i)!='\0'){

        if(*(actual.c_str()+i)<='Z' && ((*(actual.c_str()+i)>='A')))
            info_b[i]=*(actual.c_str()+i)+'a'-'A';
        else
            info_b[i]=*(info->ai_canonname+i);
        i++;
    }
    info_b[i]='\0';

    EXPECT_STREQ(info_a, info_b);
    
    freeaddrinfo(info);

 

}
