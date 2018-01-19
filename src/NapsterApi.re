open Js.Result;
open Js.Promise;
open Superagent;
open Option.Infix;
open DataTypes;

module type T = { let apiKey: string; };

module Make = (Config: T) => {
    exception BadResponse(Js.Json.t, option(string));

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

    [@autoserialize] type me = { me: Member.t };
    let me = (accessToken) =>
        _performGet(accessToken, "/me", [])
            |> then_((respJson) =>
                switch (me__from_json(respJson)) {
                    | Error(key) => reject(BadResponse(respJson, key))
                    | Ok(v) => resolve(v)
                }
            );

    [@autoserialize]
    type search = {
        meta: Search.meta,
        search: Search.body
    };

    type searchTypes =
        | Album
        | Artist
        | Track
        | Playlist
        | Tag;

    let _searchTypeString = fun
        | Album => "album"
        | Artist => "artist"
        | Track => "track"
        | Playlist => "playlist"
        | Tag => "tag";

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
                switch (search__from_json(respJson)) {
                    | Error(key) => reject(BadResponse(respJson, key))
                    | Ok(v) => resolve(v)
                }
            );
    };
};
