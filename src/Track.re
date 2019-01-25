[@decco]
type format = {
    bitrate: int,
    name: string
};

[@decco]
type t = {
    id: string,
    index: int,
    disc: int,
    href: string,
    playbackSeconds: int,
    isExplicit: bool,
    isStreamable: bool,
    name: string,
    isrc: option(string),
    shortcut: string,
    amg: option(string),
    blurbs: array(string),
    artistId: string, /* artist ID */
    artistName: string,
    albumName: string,
    albumId: string, /* album ID */
    formats: array(format),
    contributors: AdditionalData.contributingArtists,
    previewURL: string
};