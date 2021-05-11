package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "server",
    srcs = ["server.cc"],
    deps = [":high_score_server"],
)

cc_library(
    name = "high_score_server",
    srcs = ["high_score_server.cc"],
    hdrs = ["high_score_server.h"],
    deps = ["@libgam//:server"],
)
