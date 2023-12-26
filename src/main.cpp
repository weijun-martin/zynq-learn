#include <iostream>

#include <libwebsockets.h>

static int callback_my_protocol(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len)
{
    switch (reason)
    {
    case LWS_CALLBACK_ESTABLISHED:
        printf("Connection established\n");
        break;
    case LWS_CALLBACK_RECEIVE:
        printf("Received data: %s\n", (char *)in);
        lws_write(wsi, (unsigned char *)in, len, LWS_WRITE_TEXT);
        break;
    case LWS_CALLBACK_CLOSED:
        printf("Connection closed\n");
        break;
    default:
        break;
    }
    return 0;
}

static struct lws_protocols protocols[] = {
    {
        "my-protocol",
        callback_my_protocol,
        0,
        0,
    },
    {NULL, NULL, 0, 0} // 结束标记
};

int main(int argc, char *argv[])
{
    struct lws_context_creation_info info;
    memset(&info, 0, sizeof(info));
    info.port = 8080;
    info.protocols = protocols;
    struct lws_context *context = lws_create_context(&info);

    std::cout << "Number of arguments: " << argc << std::endl;
    for (int i = 0; i < argc; i++)
    {
        std::cout << "Argument " << i << ": " << argv[i] << std::endl;
    }
    while (1)
    {
        lws_service(context, 50);
    }
    lws_context_destroy(context);
    return 0;
}