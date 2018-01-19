open Js.Promise;
open PromiseEx;
open Option.Infix;

module NapsterApi = Api.Make({
    let apiKey = "N2U0MWNjYjEtMzZlMC00ZDk0LWE5NjctYmEwODljNjVjYzE3";
});

let openExn = [@bs.open] (fun
    | DataTypes.BadResponse(json, badKey) => (json, badKey)
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
        result.NapsterApi.search.data.artists |? [||]
            |> Js.Array.map(({ DataTypes.Artist.id, name }) => Js.log3(id,":",name))
            |> ignore;

        result.NapsterApi.search.data.albums |? [||]
            |> Js.Array.map(({ DataTypes.Album.id, name }) => Js.log3(id,":",name))
            |> ignore;

        result.NapsterApi.search.data.tracks |? [||]
            |> Js.Array.map(({ DataTypes.Track.id, name }) => Js.log3(id,":",name))
            |> ignore;

        result.NapsterApi.search.data.playlists |? [||]
            |> Js.Array.map(({ DataTypes.Playlist.id, name }) => Js.log3(id,":",name))
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