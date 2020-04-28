#pragma once
#include "influxdb.hpp"
#include <iostream>
#include <string>

using namespace std;

namespace FLIDB {
    class FLinfluxDB
    {
        private:
        FLinfluxDB();
        influxdb_cpp::server_info* serverinfo;
        
        public:
        FLinfluxDB(string host, int port, string dbname);
        void PostData(string measurename, string countrytag, string regiontag, float data);
        void ShowData();
    };
}
