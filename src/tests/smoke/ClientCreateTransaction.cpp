
#include <gtest/gtest.h>
#include "Client.h"

TEST(test_client_transaction, AddFunction)
{
    Client* client = new Client();

    auto t = client->createTransaction();

    ASSERT_NE(t.get(), nullptr);
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}