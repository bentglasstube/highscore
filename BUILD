package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "highscore",
    srcs = ["main.cc"],
    data = ["//content"],
    deps = [
        "@libgam//:game",
        ":high_score_screen"
    ],
)

cc_binary(
    name = "server",
    srcs = ["server.cc"],
    deps = [":high_score_server"],
)

cc_binary(
    name = "client",
    srcs = ["client.cc"],
    deps = [":high_score_client"],
)

cc_library(
    name = "score",
    srcs = ["score.cc"],
    hdrs = ["score.h"],
)

cc_library(
    name = "high_score_client",
    srcs = ["high_score_client.cc"],
    hdrs = ["high_score_client.h"],
    deps = [
        "@libgam//:client",
        ":score",
    ],
)

cc_library(
    name = "high_score_screen",
    srcs = ["high_score_screen.cc"],
    hdrs = ["high_score_screen.h"],
    deps = [
        "@libgam//:screen",
        "@libgam//:text",
        ":high_score_client",
    ],
)

cc_library(
    name = "high_score_server",
    srcs = ["high_score_server.cc"],
    hdrs = ["high_score_server.h"],
    deps = [
        "@libgam//:server",
        ":score",
    ],
)
