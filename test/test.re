open Js.Promise;
open PromEx;
open OptEx.Operators;
open NapsterApi;

module NapsterApi = NapsterApi.Make({
    let apiKey = "N2U0MWNjYjEtMzZlMC00ZDk0LWE5NjctYmEwODljNjVjYzE3";
});

let openExn = [@bs.open] (fun
    | NapsterTypes.BadResponse(json, badKey) => (json, badKey)
);

let accessCode = "ZDFmOGEwYTItMDM1Ni00NmZlLWFkYWItNGZlODc5MTcyZGEw";

NapsterApi.me(accessCode)
    |> map(Js.log2("me"))
    |> catch((exn) => {
        Js.log2("me error", exn);
        resolve ();
    });

NapsterApi.search(accessCode, "disintegration")
    |> map((result) => {
        open Search;

        result.search.data.artists |? [||]
            |> Js.Array.map(({ Artist.id, name }) => Js.log3(id,":",name))
            |> ignore;

        result.search.data.albums |? [||]
            |> Js.Array.map(({ Album.id, name }) => Js.log3(id,":",name))
            |> ignore;

        result.search.data.tracks |? [||]
            |> Js.Array.map(({ Track.id, name }) => Js.log3(id,":",name))
            |> ignore;

        result.search.data.playlists |? [||]
            |> Js.Array.map(({ Playlist.id, name }) => Js.log3(id,":",name))
            |> ignore;
    })
    |> catch((exn) => {
        switch (openExn(exn)) {
            | None => Js.log2("unknown error", exn)
            | Some((json, badKey)) => {
                Js.log3("Bad response", json, badKey);
            }
        };
        resolve();
    });
