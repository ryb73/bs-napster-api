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
