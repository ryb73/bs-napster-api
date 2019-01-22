open Belt.Result;
open Reduice.Promise;
open Superagent;
open NapsterTypes;
open OptEx.Operators;

module type T = { let apiKey: string; };

module Make = (Config: T) => {
    let _performGet = (accessToken, path, params) => {
        get("https://api.napster.com/v2.2" ++ path)
            |> setHeader(Authorization(Bearer, accessToken))
            |> queryMultiple(Js.Dict.fromList(params))
            |> query("apikey", Config.apiKey)
            |> end_
            |> PromEx.map((resp) =>
                switch (resp.body) {
                    | None => Js.Exn.raiseError("No response body")
                    | Some(body) => body
                }
            );
    };

    [@decco] type me = { me: Member.t };
    let me = (accessToken) =>
        _performGet(accessToken, "/me", [])
            |> then_((respJson) =>
                switch (me_decode(respJson)) {
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
                switch (Search.t_decode(respJson)) {
                    | Error(key) => reject(BadResponse(respJson, key))
                    | Ok(v) => resolve(v)
                }
            );
    };
};
