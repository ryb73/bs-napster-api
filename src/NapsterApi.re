open Js.Result;
open Js.Promise;
open Superagent;

module type T = {
    let apiKey : string;
};

module Make = fun (Config : T) => {
    let _performGet accessToken path => {
        get ("https://api.napster.com/v2.2" ^ path)
            |> Get.setHeader (Authorization Bearer accessToken)
            |> Get.query @@ Js.Dict.fromList [ ("apikey", Config.apiKey) ]
            |> Get.end_
            |> then_ (fun (result : (Js.Result.t result string)) => {
                resolve @@ switch result {
                    | Error err => failwith err
                    | Ok resp => switch (Js.Nullable.to_opt resp##body) {
                        | None => failwith "No response body"
                        | Some body => body
                    };
                };
            });
    };

    type member = {
        id: string,
        realName: string,
        screenName: string,
        bio: option string,
        location: option string,
        gender: option string,
        visibility: string,
        role: string,
        followingCount: int,
        followerCount: int,
        avatar: string,
        avatarId: string,
        defaultAvatar: string, /* "true" or "false" */
        avatarVersion: int
    };

    type me = {
        me: member
    };

    let me accessToken => {
        _performGet accessToken "/me"
            |> then_ (fun respJson => {
                switch (me__from_json respJson) {
                    | Error (Some key) => failwith @@ "Deserialization error (key: " ^ key ^ ")"
                    | Error _ => failwith "Deserialization error"
                    | Ok v => resolve v
                }
            });
    };
};