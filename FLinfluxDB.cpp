#include "FLinfluxDB.hpp"


namespace FLIDB {
    FLinfluxDB::FLinfluxDB(string host, int port, string dbname){
        serverinfo = new influxdb_cpp::server_info(host,port,dbname);
        cout<<"Подключился к базе данных "<<dbname<<endl;
    }
    void FLinfluxDB::PostData(string measurename, string countrytag, string regiontag, float data)
    {
    string response;
    int ret = influxdb_cpp::builder()
        .meas(measurename)
    .tag("country",countrytag)
    .tag("region",regiontag)
    .field("sunvalue",data)
    .post_http(*serverinfo,&response);

    cout << ret << endl << response << endl;
    }

    void FLinfluxDB::ShowData()
    {
        string response;
        influxdb_cpp::query(response, "show databases", *serverinfo);
        cout << response << endl;
    }

}

