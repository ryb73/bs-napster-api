open Bluebird;
open Option.Infix;

module BluebirdEx = PromiseEx.Make(Bluebird);
open BluebirdEx;

module NapsterApi = Api.Make({
    let apiKey = "N2U0MWNjYjEtMzZlMC00ZDk0LWE5NjctYmEwODljNjVjYzE3";
});

let openExn = [@bs.open] (fun
    | Types.BadResponse(json, badKey) => (json, badKey)
);

let accessCode = "ZDFmOGEwYTItMDM1Ni00NmZlLWFkYWItNGZlODc5MTcyZGEw";

/* NapsterApi.me(accessCode)
    |> map(Js.log2("me"))
    |> catch((exn) => {
        Js.log2("me error", exn);
        resolve ();
    }); */

NapsterApi.search(accessCode, "disintegration")
    |> map((result) => {
        result.Types.Search.search.data.artists |? [||]
            |> Js.Array.map(({ Types.Artist.id, name }) => Js.log3(id,":",name))
            |> ignore;

        result.Types.Search.search.data.albums |? [||]
            |> Js.Array.map(({ Types.Album.id, name }) => Js.log3(id,":",name))
            |> ignore;

        result.Types.Search.search.data.tracks |? [||]
            |> Js.Array.map(({ Types.Track.id, name }) => Js.log3(id,":",name))
            |> ignore;

        result.Types.Search.search.data.playlists |? [||]
            |> Js.Array.map(({ Types.Playlist.id, name }) => Js.log3(id,":",name))
            |> ignore;
    })
    |> catch((exn) => {
        switch (openExn(exn)) {
            | None => Js.log2("unknown error", exn)
            | Some((json, badKey)) => {
                /* [%bs.raw "console.log(JSON.stringify(match[0][0].search.data.playlists[2].images, null, 2))"]; */
                Js.log3("Bad response", json, badKey);
            }
        };
        resolve();
    });