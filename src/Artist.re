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
