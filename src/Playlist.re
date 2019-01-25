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
