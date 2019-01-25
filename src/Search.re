[@decco]
type meta = {
    totalCount: int,
    returnedCount: int
};

[@decco]
type data = {
    albums: option(array(Album.t)),
    artists: option(array(Artist.t)),
    tracks: option(array(Track.t)),
    playlists: option(array(Playlist.t)),
    tags: option(array(Tag.t))
};

[@decco]
type body = {
    query: string,
    data: data,
    order: array(string) /* various IDs */
};

[@decco]
type t = {
    meta: meta,
    search: body
};

type searchTypes =
    | Albums
    | Artists
    | Tracks
    | Playlists
    | Tags;
