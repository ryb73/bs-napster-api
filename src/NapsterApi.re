open Js.Result;
open Js.Promise;
open Superagent;

module type T = { let apiKey: string; };

module Make = (Config: T) => {
    let _performGet = (accessToken, path) =>
        get("https://api.napster.com/v2.2" ++ path)
            |> Get.setHeader(Authorization(Bearer, accessToken))
            |> Get.query(Js.Dict.fromList([("apikey", Config.apiKey)]))
            |> Get.end_
            |> then_((resp) =>
                resolve(
                    switch (resp.body) {
                        | None => Js.Exn.raiseError("No response body")
                        | Some(body) => body
                    }
                )
            );

    [@autoserialize]
    type member = {
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
        avatarVersion: int
    };

    [@autoserialize] type me = { me: member };
    let me = (accessToken) =>
        _performGet(accessToken, "/me")
            |> then_((respJson) =>
                switch (me__from_json(respJson)) {
                    | Error(Some(key)) => Js.Exn.raiseError("Deserialization error (key: " ++ key ++ ")")
                    | Error(_) => Js.Exn.raiseError("Deserialization error")
                    | Ok(v) => resolve(v)
                }
            );
};
