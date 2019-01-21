open Decco;

exception BadResponse(Js.Json.t, decodeError);

module Member = {
    [@decco]
    type t = {
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
        avatarVersion: [@decco.codec Codecs.int64Unsafe] int64
    };
};

module Tag = {
    [@decco]
    type t = {
        id: string,
        name: string,
        isProtected: bool,
        shortcut: string,
        href: string,
        parentId: string, /* tag ID */
        childIds: array(string), /* tag IDs */
        genreId: string /* genre ID */
    };
};

module AdditionalData = {
    [@decco]
    type contributingArtists = {
        primaryArtist: string /* artist ID */
    };
};

module Album = {
    [@decco]
    type discographies = {
        main: option(array(string)), /* art IDs */
        singlesAndEPs: option(array(string)),
    };

    [@decco]
    type t = {
        id: string,
        upc: option(string),
        shortcut: string,
        amg: option(string),
        href: string,
        name: string,
        released: string, /* TODO: parse timestamp */
        originallyReleased: string,
        label: string,
        copyright: string,
        tags: array(string),
        discCount: int,
        trackCount: int,
        isExplicit: bool,
        isSingle: bool,
        isStreamable: bool,
        accountPartner: string,
        artistName: string,
        contributingArtists: AdditionalData.contributingArtists,
        discographies: option(discographies)
    };
};


module Artist = {
    [@decco]
    type bio = {
        title: string,
        author: string,
        publishDate: string,
        bio: string
    };

    [@decco]
    type albumGroups = {
        main: option(array(string)), /* album IDs */
        compilations: option(array(string)),
        singlesAndEPs: option(array(string)),
        others: option(array(string))
    };

    [@decco]
    type t = {
        id: string,
        href: string,
        name: string,
        shortcut: string,
        amg: option(string),
        blurbs: array(string),
        bios: option(array(bio)),
        albumGroups: albumGroups
    };
};

module Track = {
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
};

module Playlist = {
    [@decco]
    type image = {
        id: string,
        url: option(string),
        contentId: string,
        width: option(int),
        height: option(int),
        isDefault: bool,
        version: int,
        imageType: string
    };

    [@decco]
    type t = {
        id: string,
        name: string,
        modified: string, /* timestamp */
        href: string,
        trackCount: int,
        privacy: string, /* enum? */
        images: array(image),
        description: string,
        favoriteCount: int,
        freePlayCompliant: bool
    };
};

module Search = {
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
};