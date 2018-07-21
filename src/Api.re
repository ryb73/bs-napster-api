open Js.Result;
open Bluebird;
open Superagent;
open Option.Infix;
open Types;

module type T = { let apiKey: string; };

module Make = (Config: T) => {
    let _performGet = (accessToken, path, params) => {
        get("https://api.napster.com/v2.2" ++ path)
            |> Get.setHeader(Authorization(Bearer, accessToken))
            |> Get.query(Js.Dict.fromList(List.append([ ("apikey", Config.apiKey) ], params)))
            |> Get.end_
            |> then_((resp) =>
                resolve(
                    switch (resp.body) {
                        | None => Js.Exn.raiseError("No response body")
                        | Some(body) => body
                    }
                )
            );
    };

    [@decco] type me = { me: Member.t };
    let me = (accessToken) =>
        _performGet(accessToken, "/me", [])
            |> then_((respJson) =>
                switch (me__from_json(respJson)) {
                    | Error(key) => reject(BadResponse(respJson, key))
                    | Ok(v) => resolve(v)
                }
            );

    let _searchTypeString = fun
        | Search.Albums => "album"
        | Artists => "artist"
        | Tracks => "track"
        | Playlists => "playlist"
        | Tags => "tag";

    let search = (~types=?, accessToken, query) => {
        let typeString = types |? [||]
            |> Js.Array.map(_searchTypeString)
            |> Js.Array.joinWith(",");

        _performGet
            (accessToken, "/search", [
                ("query", query),
                ("type", typeString)
            ])
            |> then_((respJson) =>
                switch (Search.t__from_json(respJson)) {
                    | Error(key) => reject(BadResponse(respJson, key))
                    | Ok(v) => resolve(v)
                }
            );
    };
};
