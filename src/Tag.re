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
