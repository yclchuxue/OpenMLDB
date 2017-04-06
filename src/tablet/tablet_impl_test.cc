//
// tablet_impl_test.cc
// Copyright (C) 2017 4paradigm.com
// Author wangtaize 
// Date 2017-04-05
//

#include "tablet/tablet_impl.h"
#include "proto/tablet.pb.h"
#include "gtest/gtest.h"

namespace rtidb {
namespace tablet {

class MockClosure : public ::google::protobuf::Closure {

public:
    MockClosure() {}
    ~MockClosure() {}
    void Run() {}

};

class TabletImplTest : public ::testing::Test {

public:
    TabletImplTest() {}
    ~TabletImplTest() {}
};


TEST_F(TabletImplTest, CreateTable) {
    TabletImpl tablet;
    ::rtidb::api::CreateTableRequest request;
    request.set_name("t0");
    request.set_tid(1);
    request.set_pid(1);
    request.set_ttl(1);
    ::rtidb::api::CreateTableResponse response;
    MockClosure closure;
    tablet.CreateTable(NULL, &request, &response,
            &closure);
    ASSERT_EQ(0, response.code());
    tablet.CreateTable(NULL, &request, &response,
            &closure);
    ASSERT_EQ(-2, response.code());
}

TEST_F(TabletImplTest, Put) {
    TabletImpl tablet;
    ::rtidb::api::CreateTableRequest request;
    request.set_name("t0");
    request.set_tid(1);
    request.set_pid(1);
    request.set_ttl(1);
    ::rtidb::api::CreateTableResponse response;
    MockClosure closure;
    tablet.CreateTable(NULL, &request, &response,
            &closure);
    ASSERT_EQ(0, response.code());

    ::rtidb::api::PutRequest prequest;
    prequest.set_pk("test1");
    prequest.set_time(9527);
    prequest.set_value("test0");
    prequest.set_tid(0);
    ::rtidb::api::PutResponse presponse;
    tablet.Put(NULL, &prequest, &presponse,
            &closure);
    ASSERT_EQ(10, presponse.code());
    prequest.set_tid(1);
    tablet.Put(NULL, &prequest, &presponse,
            &closure);
    ASSERT_EQ(0, presponse.code());
}

TEST_F(TabletImplTest, Scan) {
    TabletImpl tablet;
    ::rtidb::api::CreateTableRequest request;
    request.set_name("t0");
    request.set_tid(1);
    request.set_pid(1);
    request.set_ttl(1);
    ::rtidb::api::CreateTableResponse response;
    MockClosure closure;
    tablet.CreateTable(NULL, &request, &response,
            &closure);
    ASSERT_EQ(0, response.code());

    ::rtidb::api::PutRequest prequest;
    prequest.set_pk("test1");
    prequest.set_time(9527);
    prequest.set_value("test0");
    prequest.set_tid(0);
    ::rtidb::api::PutResponse presponse;
    tablet.Put(NULL, &prequest, &presponse,
            &closure);
    ASSERT_EQ(10, presponse.code());
    prequest.set_tid(1);
    tablet.Put(NULL, &prequest, &presponse,
            &closure);
    ASSERT_EQ(0, presponse.code());
}



}
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


