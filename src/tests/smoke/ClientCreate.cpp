
#include <gtest/gtest.h>
#include "Client.h"

TEST(test_client, AddFunction)
{
    Client* client = new Client();

    ASSERT_NE(client, nullptr);

    delete client;
    client = nullptr;

    ASSERT_EQ(client, nullptr);
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}