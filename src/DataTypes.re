exception BadResponse(Js.Json.t, option(string));

module Member = {
    [@autoserialize]
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
        avatarVersion: int
    };
};

module Tag = {
    [@autoserialize]
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
    [@autoserialize]
    type contributingArtists = {
        primaryArtist: string /* artist ID */
    };
};

module Album = {
    [@autoserialize]
    type discographies = {
        main: [@autoserialize.nullable] option(array(string)), /* art IDs */
        singlesAndEPs: [@autoserialize.nullable] option(array(string)),
    };

    [@autoserialize]
    type t = {
        id: string,
        upc: string,
        shortcut: string,
        amg: [@autoserialize.nullable] option(string),
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
        discographies: discographies
    };
};


module Artist = {
    [@autoserialize]
    type bio = {
        title: string,
        author: string,
        publishDate: string,
        bio: string
    };

    [@autoserialize]
    type albumGroups = {
        main: [@autoserialize.nullable] option(array(string)), /* album IDs */
        compilations: [@autoserialize.nullable] option(array(string)),
        singlesAndEPs: [@autoserialize.nullable] option(array(string)),
        others: [@autoserialize.nullable] option(array(string))
    };

    [@autoserialize]
    type t = {
        id: string,
        href: string,
        name: string,
        shortcut: string,
        amg: [@autoserialize.nullable] option(string),
        blurbs: array(string),
        bios: [@autoserialize.nullable] option(array(bio)),
        albumGroups: albumGroups
    };
};

module Track = {
    [@autoserialize]
    type format = {
        bitrate: int,
        name: string
    };

    [@autoserialize]
    type t = {
        id: string,
        index: int,
        disc: int,
        href: string,
        playbackSeconds: int,
        isExplicit: bool,
        isStreamable: bool,
        name: string,
        isrc: string,
        shortcut: string,
        amg: [@autoserialize.nullable] option(string),
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
    [@autoserialize]
    type image = {
        id: string,
        url: [@autoserialize.nullable] option(string),
        contentId: string,
        width: [@autoserialize.nullable] option(int),
        height: [@autoserialize.nullable] option(int),
        isDefault: bool,
        version: int,
        imageType: string
    };

    [@autoserialize]
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
    [@autoserialize]
    type meta = {
        totalCount: int,
        returnedCount: int
    };

    [@autoserialize]
    type data = {
        albums: [@autoserialize.nullable] option(array(Album.t)),
        artists: [@autoserialize.nullable] option(array(Artist.t)),
        tracks: [@autoserialize.nullable] option(array(Track.t)),
        playlists: [@autoserialize.nullable] option(array(Playlist.t)),
        tags: [@autoserialize.nullable] option(array(Tag.t))
    };

    [@autoserialize]
    type body = {
        query: string,
        data: data,
        order: array(string) /* various IDs */
    };
};