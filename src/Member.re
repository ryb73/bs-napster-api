open Decco;

[@decco]
type t = {
    id: string,
    realName: string,
    screenName: string,
    bio: option(string),
    location: option(string),
    gender: option(string),
    visibility: string,
    role: string,
    followingCount: int,
    followerCount: int,
    avatar: string,
    avatarId: string,
    defaultAvatar: string, /* "true" or "false" */
    avatarVersion: [@decco.codec Codecs.int64Unsafe] int64
};
