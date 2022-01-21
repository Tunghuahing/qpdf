//
// This file is automatically generated by generate_auto_job.
// Edits will be automatically overwritten if the build is
// run in maintainer mode.
//
static void add_help_1(QPDFArgParser& ap)
{
ap.addHelpTopic("usage", "basic invocation", R"(Read a PDF file, apply transformations or modifications, and write
a new PDF file.

Usage: qpdf infile [options] [outfile]
   OR  qpdf help-option

- infile, options, and outfile may be in any order as long as infile
  precedes outfile.
- Use --empty in place of an input file for a zero-page, empty input
- Use --replace-input in place of an output file to overwrite the
  input file with the output
- outfile may be - to write to stdout; reading from stdin is not supported
- @filename is an argument file; each line is treated as a separate
  command-line argument
- @- may be used to read arguments from stdin
- Later options may override earlier options if contradictory
)");
ap.addOptionHelp("--empty", "usage", "empty input file", R"(Use in place of infile for an empty input. Especially useful
with --pages.
)");
ap.addOptionHelp("--replace-input", "usage", "replace input with output", R"(Use in place of outfile to overwrite the input file with the output.
)");
ap.addHelpTopic("exit-status", "meanings of qpdf's exit codes", R"(Meaning of exit codes:

0: no errors or warnings
1: not used by qpdf but may be used by the shell if unable to invoke qpdf
2: errors detected
3: warnings detected, unless --warning-exit-0 is given
)");
ap.addOptionHelp("--warning-exit-0", "exit-status", "exit 0 even with warnings", R"(Use exit status 0 instead of 3 when warnings are present. When
combined with --no-warn, warnings are completely ignored.
)");
ap.addHelpTopic("completion", "shell completion", R"(Shell completion is supported with bash and zsh. Use
eval $(qpdf --completion-bash) or eval $(qpdf --completion-zsh)
to enable. The QPDF_EXECUTABLE environment variable overrides the
path to qpdf that these commands output.
)");
ap.addOptionHelp("--completion-bash", "completion", "enable bash completion", R"(Output a command that enables bash completion
)");
ap.addOptionHelp("--completion-zsh", "completion", "enable zsh completion", R"(Output a command that enables zsh completion
)");
ap.addHelpTopic("help", "information about qpdf", R"(Help options provide some information about qpdf itself. Help
options are only valid as the first and only command-line argument.
)");
ap.addOptionHelp("--help", "help", "provide help", R"(Display help information. Run qpdf --help for information about
how to get help on various topics.
)");
ap.addOptionHelp("--version", "help", "show qpdf version", R"(Display the version of qpdf.
)");
ap.addOptionHelp("--copyright", "help", "show copyright information", R"(Display copyright and license information.
)");
ap.addOptionHelp("--show-crypto", "help", "show available crypto providers", R"(Show a list of available crypto providers, one per line. The
default provider is shown first.
)");
ap.addHelpTopic("general", "general options", R"(General options control qpdf's behavior in ways that are not
directly related to the operation it is performing.
)");
ap.addOptionHelp("--password", "general", "specify password", R"(--password=password

Specify a password for an encrypted, password-protected file.
Not needed for encrypted files with no password.
)");
ap.addOptionHelp("--password-file", "general", "read password from a file", R"(--password-file=filename

The first line of the specified file is used as the password.
This is used in place of the --password option.
)");
ap.addOptionHelp("--verbose", "general", "print additional information", R"(Output additional information about various things qpdf is
doing, including information about files created and operations
performed.
)");
ap.addOptionHelp("--progress", "general", "show progress when writing", R"(Indicate progress when writing files.
)");
ap.addOptionHelp("--no-warn", "general", "suppress printing warning messages", R"(Suppress printing warning messages. If warnings were
encountered, qpdf still exits with exit status 3.
Use --warning-exit-0 with --no-warn to completely ignore
warnings.
)");
}
static void add_help_2(QPDFArgParser& ap)
{
ap.addOptionHelp("--deterministic-id", "general", "generate ID deterministically", R"(Generate a secure, random document ID only using static
information, such as the page contents. Does not use the file's
name or attributes or the current time.
)");
ap.addOptionHelp("--allow-weak-crypto", "general", "allow insecure cryptographic algorithms", R"(All creation of files with weak cryptographic algorithms. This
option is necessary to create 40-bit files or 128-bit files that
use RC4 encryption.
)");
ap.addOptionHelp("--keep-files-open", "general", "manage keeping multiple files open", R"(--keep-files-open=[yn]

When qpdf needs to work with many files, as when merging large
numbers of files, explicitly indicate whether files should be
kept open. The default behavior is to determine this based on
the number of files.
)");
ap.addOptionHelp("--keep-files-open-threshold", "general", "set threshold for --keep-files-open", R"(--keep-files-open-threshold=count

Set the threshold used by --keep-files-open, overriding the
default value of 200.
)");
ap.addHelpTopic("advanced-control", "tweak qpdf's behavior", R"(Advanced control options control qpdf's behavior in ways that would
normally never be needed by a user but that may be useful to
developers or people investigating problems with specific files.
)");
ap.addOptionHelp("--password-is-hex-key", "advanced-control", "provide hex-encoded encryption key", R"(Provide the underlying file encryption key has a hex-encoded
string rather than supplying a password. This is an expert
option.
)");
ap.addOptionHelp("--suppress-password-recovery", "advanced-control", "don't try different password encodings", R"(Suppress qpdf's behavior of attempting different encodings of a
password that contains non-ASCII Unicode characters if the first
attempt doesn't succeed.
)");
ap.addOptionHelp("--password-mode", "advanced-control", "tweak how qpdf encodes passwords", R"(--password-mode={mode}

Fine-tune how qpdf controls encoding of Unicode passwords. Valid
options are auto, bytes, hex-bytes, and unicode.
)");
ap.addOptionHelp("--suppress-recovery", "advanced-control", "suppress error recovery", R"(Avoid attempting to recover when errors are found in a file's
cross reference table or stream lengths.
)");
ap.addOptionHelp("--ignore-xref-streams", "advanced-control", "use xref tables rather than streams", R"(Ignore any cross-reference streams in the file, falling back to
cross-reference tables or triggering document recovery.
)");
ap.addHelpTopic("transformation", "make structural PDF changes", R"(The options below tell qpdf to apply transformations that change
the structure without changing the content.
)");
ap.addOptionHelp("--linearize", "transformation", "linearize (web-optimize) output", R"(Create linearized (web-optimized) output files.
)");
ap.addOptionHelp("--encrypt", "transformation", "start encryption options", R"(--encrypt user owner key-length [ options ] --

Run qpdf --help=encryption for details.
)");
ap.addOptionHelp("--decrypt", "transformation", "remove encryption from input file", R"(Create an unencrypted output file even if the input file was
encrypted. Normally qpdf preserves whatever encryption was
present on the input file. This option overrides that behavior.
)");
ap.addOptionHelp("--copy-encryption", "transformation", "copy another file's encryption details", R"(--copy-encryption=file

Copy encryption details from the specified file instead of
preserving the input file's encryption. Use --encryption-file-password
to specify the encryption file's password.
)");
ap.addOptionHelp("--encryption-file-password", "transformation", "supply password for --copy-encryption", R"(--encryption-file-password=password

If the file named in --copy-encryption requires a password, use
this option to specify the password.
)");
ap.addOptionHelp("--qdf", "transformation", "enable viewing PDF code in a text editor", R"(Create a PDF file suitable for viewing in a text editor and even
editing. This is to edit the PDF code, not the page contents.
All streams that can be uncompressed are uncompressed, and
content streams are normalized, among other changes. The
companion tool "fix-qdf" can be used to repair hand-edited QDF
files. QDF is a feature specific to the qpdf tool. There is a
chapter about it in the manual.
)");
ap.addOptionHelp("--no-original-object-ids", "transformation", "omit original object ID in qdf", R"(Omit comments in a QDF file indicating the object ID an object
had in the original file.
)");
ap.addOptionHelp("--compress-streams", "transformation", "compress uncompressed streams", R"(--compress-streams=[yn]

Setting --compress-streams=n prevents qpdf from compressing
uncompressed streams. This can be useful if you are leaving some
streams uncompressed intentionally.
)");
}
static void add_help_3(QPDFArgParser& ap)
{
ap.addOptionHelp("--decode-level", "transformation", "control which streams to uncompress", R"(--decode-level=parameter

When uncompressing streams, control which types of compression
schemes should be uncompressed:
- none: don't uncompress anything
- generalized: uncompress streams compressed with a
  general-purpose compression algorithm. This is the default.
- specialized: in addition to generalized, also uncompress
  streams compressed with a special-purpose but non-lossy
  compression scheme
- all: in addition to specialized, uncompress streams compressed
  with lossy compression schemes like JPEG (DCT)
qpdf does not know how to uncompress all compression schemes.
)");
ap.addOptionHelp("--stream-data", "transformation", "control stream compression", R"(--stream-data=parameter

This option controls how streams are compressed in the output.
It is less granular than the newer options, --compress-streams
and --decode-level.

Parameters:
- compress: same as --compress-streams=y --decode-level=generalized
- preserve: same as --compress-streams=n --decode-level=none
- uncompress: same as --compress-streams=n --decode-level=generalized
)");
ap.addOptionHelp("--recompress-flate", "transformation", "uncompress and recompress flate", R"(The default generalized compression scheme used by PDF is flate,
which is the same as used by zip and gzip. Usually qpdf just
leaves these alone. This option tells qpdf to uncompress and
recompress streams compressed with flate. This can be useful
when combined with --compression-level.
)");
ap.addOptionHelp("--compression-level", "transformation", "set compression level for flate", R"(--compression-level=level

Set a compression level from 1 (least, fastest) to 9 (most,
slowest) when compressing files with flate (used in zip and
gzip), which is the default compression for most PDF files.
You need --recompress-flate with this option if you want to
change already compressed streams.
)");
ap.addOptionHelp("--normalize-content", "transformation", "fix newlines in content streams", R"(--normalize-content=[yn]

Normalize newlines to UNIX-style newlines in PDF content
streams, which is useful for viewing them in a programmer's text
editor across multiple platforms. This is also turned on by
--qdf.
)");
ap.addOptionHelp("--object-streams", "transformation", "control use of object streams", R"(--object-streams=mode

Control what qpdf does regarding object streams. Options:
- preserve: preserve original object streams, if any (the default)
- disable: create output files with no object streams
- generate: create object streams, and compress objects when possible
)");
ap.addOptionHelp("--preserve-unreferenced", "transformation", "preserve unreferenced objects", R"(Preserve all objects from the input even if not referenced.
)");
ap.addOptionHelp("--remove-unreferenced-resources", "transformation", "remove unreferenced page resources", R"(--remove-unreferenced-resources=parameter

Remove from a page's resource dictionary any resources that are
not referenced in the page's contents. Parameters: "auto"
(default), "yes", "no".
)");
ap.addOptionHelp("--preserve-unreferenced-resources", "transformation", "use --remove-unreferenced-resources=no", R"(Synonym for --remove-unreferenced-resources=no. Use that instead.
)");
ap.addOptionHelp("--newline-before-endstream", "transformation", "force a newline before endstream", R"(For an extra newline before endstream. Using this option enables
qpdf to preserve PDF/A when rewriting such files.
)");
ap.addOptionHelp("--coalesce-contents", "transformation", "combine content streams", R"(If a page has an array of content streams, concatenate them into
a single content stream.
)");
ap.addOptionHelp("--externalize-inline-images", "transformation", "convert inline to regular images", R"(Convert inline images to regular images.
)");
ap.addOptionHelp("--ii-min-bytes", "transformation", "set minimum size for --externalize-inline-images", R"(--ii-min-bytes=size-in-bytes

Don't externalize inline images smaller than this size. The
default is 1,024. Use 0 for no minimum.
)");
ap.addOptionHelp("--min-version", "transformation", "set minimum PDF version", R"(--min-version=version

Force the PDF version of the output to be at least the
specified version.
)");
ap.addOptionHelp("--force-version", "transformation", "set output PDF version", R"(--force-version=version

Force the output PDF file's PDF version header to be the specified
value, even if the file uses features that may not be available
in that version.
)");
ap.addHelpTopic("page-ranges", "page range syntax", R"(A full description of the page range syntax, with examples, can be
found in the manual. Summary:

- a,b,c    pages a, b, and c
- a-b      pages a through b inclusive; if a > b, this counts down
- r<n>     where <n> represents a number is the <n>th page from the end
- z        the last page, same as r1

You can append :even or :odd to select every other page from the
resulting set of pages, where :odd starts with the first page and
:even starts with the second page. These are odd and even pages
from the resulting set, not based on the original page numbers.
)");
ap.addHelpTopic("modification", "change parts of the PDF", R"(Modification options make systematic changes to certain parts of
the PDF, causing the PDF to render differently from the original.
)");
ap.addOptionHelp("--pages", "modification", "begin page selection", R"(--pages file [ --password=password ] [ page-range ] [ ... ] --

Run qpdf --help=page-selection for details.
)");
ap.addOptionHelp("--collate", "modification", "collate with --pages", R"(--collate=n

Collate rather than concatenate pages specified with --pages.
With a numeric parameter, collate in groups of n. The default
is 1. Run qpdf --help=page-selection for additional details.
)");
}
static void add_help_4(QPDFArgParser& ap)
{
ap.addOptionHelp("--split-pages", "modification", "write pages to separate files", R"(--split-pages=[n]

This option causes qpdf to create separate output files for each
page or group of pages rather than a single output file.

File names are generated from the specified output file as follows:

- If the string %d appears in the output file name, it is replaced with a
  zero-padded page range starting from 1
- Otherwise, if the output file name ends in .pdf (case insensitive), a
  zero-padded page range, preceded by a dash, is inserted before the file
  extension
- Otherwise, the file name is appended with a zero-padded page range
  preceded by a dash.

Page ranges are single page numbers for single-page groups or first-last
for multi-page groups.
)");
ap.addOptionHelp("--overlay", "modification", "begin overlay options", R"(--overlay file [ options ] --

Overlay pages from another file on the output.
Run qpdf --help=overlay-underlay for details.
)");
ap.addOptionHelp("--underlay", "modification", "begin underlay options", R"(--underlay file [ options ] --

Underlay pages from another file on the output.
Run qpdf --help=overlay-underlay for details.
)");
ap.addOptionHelp("--flatten-rotation", "modification", "remove rotation from page dictionary", R"(Rotate a page using content commands instead of page-level
metadata. This can be useful if a broken PDF viewer fails to
properly consider page rotation metadata.
)");
ap.addOptionHelp("--flatten-annotations", "modification", "push annotations into content", R"(--flatten-annotations=parameter

Push page annotations into the content streams. This may be
necessary in some case when printing or splitting files.
Parameters: "all", "print", "screen".
)");
ap.addOptionHelp("--rotate", "modification", "rotate pages", R"(--rotate=[+|-]angle[:page-range]

Rotate specified pages by multiples of 90 degrees specifying
either absolute or relative angles. "angle" may be 0, 90, 180,
or 270. You almost always want to use +angle or -angle rather
than just angle, as discussed in the manual. Run
qpdf --help=page-ranges for help with page ranges.
)");
ap.addOptionHelp("--generate-appearances", "modification", "generate appearances for form fields", R"(PDF form fields consist of values and appearances, which may be
inconsistent with each other if a form field value has been
modified without updating its appearance. This option tells qpdf
to generate new appearance streams. There are some limitations,
which are discussed in the manual.
)");
ap.addOptionHelp("--optimize-images", "modification", "use efficient compression for images", R"(Attempt to use DCT (JPEG) compression for images that fall
within certain constraints as long as doing so decreases the
size in bytes of the image. See also help for the following
options:
  --oi-min-width
  --oi-min-height
  --oi-min-area
  --keep-inline-images

The --verbose flag is useful with this option.
)");
ap.addOptionHelp("--oi-min-width", "modification", "minimum width for --optimize-images", R"(--oi-min-width=width

Don't optimize images whose width is below the specified value.
)");
ap.addOptionHelp("--oi-min-height", "modification", "minimum height for --optimize-images", R"(--oi-min-height=height

Don't optimize images whose height is below the specified value.
)");
ap.addOptionHelp("--oi-min-area", "modification", "minimum area for --optimize-images", R"(--oi-min-area=area-in-pixels

Don't optimize images whose area in pixels is below the specified value.
)");
ap.addOptionHelp("--keep-inline-images", "modification", "exclude inline images from optimization", R"(Prevent inline images from being considered by --optimize-images.
)");
ap.addOptionHelp("--remove-page-labels", "modification", "remove page labels (numbers)", R"(Exclude page labels (explicit page numbers) from the output file.
)");
ap.addHelpTopic("encryption", "create encrypted files", R"(Create encrypted files. Usage:

--encrypt user-password owner-password key-length [ options ] --

Either or both of user-password and owner-password may be empty
strings. key-length may be 40, 128, or 256. Encryption options are
terminated by "--" by itself.

40-bit encryption is insecure, as is 128-bit encryption without
AES. Use 256-bit encryption unless you have a specific reason to
use an insecure format, such as testing or compatibility with very
old viewers. You must use the --allow-weak-crypto to create
encrypted files that use insecure cryptographic algorithms. The
--allow-weak-crypto flag appears outside of --encrypt ... --
(before --encrypt or after --).

Available options vary by key length. Not all readers respect all
restrictions. Different PDF readers respond differently to various
combinations of options. Sometimes a PDF viewer may show you
restrictions that differ from what you selected. This is probably
not a bug in qpdf.

Options for 40-bit only:
  --annotate=[yn]          restrict comments, filling forms, and signing
  --extract=[yn]           restrict text/graphic extraction
  --modify=[yn]            restrict document modification
  --print=[yn]             restrict printing

Options for 128-bit or 256-bit:
  --accessibility=[yn]     restrict accessibility (usually ignored)
  --annotate=[yn]          restrict commenting/filling form fields
  --assemble=[yn]          restrict document assembly
  --extract=[yn]           restrict text/graphic extraction
  --form=[yn]              restrict filling form fields
  --modify-other=[yn]      restrict other modifications
  --modify=modify-opt      control modify access by level
  --print=print-opt        control printing access
  --cleartext-metadata     prevent encryption of metadata

For 128-bit only:
  --use-aes=[yn]           indicates whether to use AES encryption
  --force-V4               forces use of V=4 encryption handler

For 256-bit only:
  --force-R5               forces use of deprecated R=5 encryption
  --allow-insecure         allow user password with empty owner password

Values for print-opt:
  none                     disallow printing
  low                      allow only low-resolution printing
  full                     allow full printing

Values for modify-opt:
  none                     allow no modifications
  assembly                 allow document assembly only
  form                     assembly + filling in form fields and signing
  annotate                 form + commenting and modifying forms
  all                      allow full document modification
)");
ap.addOptionHelp("--accessibility", "encryption", "restrict document accessibility", R"(--accessibility=[yn]

This option is ignored except with very old encryption formats.
The current PDF specification does not allow restriction of
document accessibility. This option is not available with 40-bit
encryption.
)");
ap.addOptionHelp("--annotate", "encryption", "restrict document annotation", R"(--annotate=[yn]

Enable/disable modifying annotations including making comments
and filling in form fields. For 128-bit and 256-bit encryption,
this also enables editing, creating, and deleting form fields
unless --modify-other=n or --modify=none is also specified.
)");
ap.addOptionHelp("--assemble", "encryption", "restrict document assembly", R"(--assemble=[yn]

Enable/disable document assembly (rotation and reordering of
pages). This option is not available with 40-bit encryption.
)");
ap.addOptionHelp("--extract", "encryption", "restrict text/graphic extraction", R"(--extract=[yn]

Enable/disable text/graphic extraction for purposes other than
accessibility.
)");
ap.addOptionHelp("--form", "encryption", "restrict form filling", R"(--form=[yn]

Enable/disable whether filling form fields is allowed even if
modification of annotations is disabled. This option is not
available with 40-bit encryption.
)");
}
static void add_help_5(QPDFArgParser& ap)
{
ap.addOptionHelp("--modify-other", "encryption", "restrict other modifications", R"(--modify-other=[yn]

Enable/disable modifications not controlled by --assemble,
--annotate, or --form. --modify-other=n is implied by any of the
other --modify options. This option is not available with 40-bit
encryption.
)");
ap.addOptionHelp("--modify", "encryption", "restrict document modification", R"(--modify=modify-opt

For 40-bit files, modify-opt may only be y or n and controls all
aspects of document modification.

For 128-bit and 256-bit encryption, modify-opt values allow
enabling and disabling levels of restriction in a manner similar
to how some PDF creation tools do it. modify-opt values map to
other combinations of options as follows:

all: allow full modification (the default)
annotate: --modify-other=n
form: --modify-other=n --annotate=n
assembly: --modify-other=n --annotate=n --form=n
none: --modify-other=n --annotate=n --form=n --assemble=n
)");
ap.addOptionHelp("--print", "encryption", "restrict printing", R"(--print=print-opt

Control what kind of printing is allowed. For 40-bit encryption,
print-opt may only be y or n and enables or disables all
printing. For 128-bit and 256-bit encryption, print-opt may have
the following values:

none: disallow printing
low: allow low-resolution printing only
full: allow full printing (the default)
)");
ap.addOptionHelp("--cleartext-metadata", "encryption", "don't encrypt metadata", R"(If specified, don't encrypt document metadata even when
encrypting the rest of the document. This option is not
available with 40-bit encryption.
)");
ap.addOptionHelp("--use-aes", "encryption", "use AES with 128-bit encryption", R"(--use-aes=[yn]

Enables/disables use of the more secure AES encryption with
128-bit encryption. Specifying --use-aes=y forces the PDF
version to be at least 1.6. This option is only available with
128-bit encryption. The default is "n" for compatibility
reasons. Use 256-bit encryption instead.
)");
ap.addOptionHelp("--allow-insecure", "encryption", "allow empty owner passwords", R"(Allow creation of PDF files with empty owner passwords and
non-empty user passwords when using 256-bit encryption.
)");
ap.addOptionHelp("--force-V4", "encryption", "force V=4 in encryption dictionary", R"(This option is for testing and is never needed in practice since
qpdf does this automatically when needed.
)");
ap.addOptionHelp("--force-R5", "encryption", "use unsupported R=5 encryption", R"(Use an undocumented, unsupported, deprecated encryption
algorithm that existed only in Acrobat version IX. This option
should not be used except for compatibility testing.
)");
ap.addHelpTopic("page-selection", "select pages from one or more files", R"(Use the --pages option to select pages from multiple files. Usage:

qpdf in.pdf --pages input-file [ --password=password ] [ page-range ] \
    [ ... ] -- out.pdf

Between --pages and the -- that terminates pages option, repeat
the following:

filename [ --password=password ] [ page-range ]

Document-level information, such as outlines, tags, etc., is taken
from in.pdf is preserved in out.pdf. You can use --empty in place
of an input file to start from an empty file and just copy pages
equally from all files. You can use "." as a shorthand for the
primary input file (if not --empty). In the above example, "."
would refer to in.pdf.

Use --password=password to specify the password for a
password-protected input file. If the same input file is used more
than once, you only need to supply the password the first time. If
the page range is omitted, all pages are selected.

Run qpdf --help=page-ranges for help with page ranges.

Use --collate=n to cause pages to be collated in groups of n pages
(default 1) instead of concatenating the input.

Examples:

- Start with in.pdf and append all pages from a.pdf and the even
  pages from b.pdf, and write the output to out.pdf. Document-level
  information from in.pdf is retained. Note the use of "." to refer
  to in.pdf.

  qpdf in.pdf --pages . a.pdf b.pdf:even -- out.pdf

- Take all the pages from a.pdf, all the pages from b.pdf in
  reverse, and only pages 3 and 6 from c.pdf and write the result
  to out.pdf. Use password "x" to open b.pdf:

  qpdf --empty --pages a.pdf b.pdf --password=x z-1 c.pdf 3,6

More examples are in the manual.
)");
ap.addHelpTopic("overlay-underlay", "overlay/underlay pages from other files", R"(These options allow pages from another file to be overlaid or
underlaid on the primary output. Overlaid pages are drawn on top of
the destination page and may obscure the page. Underlaid pages are
drawn below the destination page. Usage:

{--overlay | --underlay } file
      [ --password=password ]
      [ --to=page-range ]
      [ --from=[page-range] ]
      [ --repeat=page-range ]
      --

Note the use of "--" by itself to terminate overlay/underlay options.

For overlay and underlay, a file and optional password are specified, along
with a series of optional page ranges. The default behavior is that each
page of the overlay or underlay file is imposed on the corresponding page
of the primary output until it runs out of pages, and any extra pages are
ignored. You can also give a page range with --repeat to cause
those pages to be repeated after the original pages are exhausted.

Run qpdf --help=page-ranges for help with page ranges.
)");
ap.addOptionHelp("--to", "overlay-underlay", "destination pages for underlay/overlay", R"(--to=page-range

Specify the range of pages in the primary output to apply
overlay/underlay to. See qpdf --help=page-ranges for help with
the page range syntax.
)");
ap.addOptionHelp("--from", "overlay-underlay", "source pages for underlay/overlay", R"(--from=[page-range]

Specify pages from the overlay/underlay file that are applied to
the destination pages. See qpdf --help=page-ranges for help
with the page range syntax. The page range may be omitted
if --repeat is used.
)");
ap.addOptionHelp("--repeat", "overlay-underlay", "overlay/underlay pages to repeat", R"(--repeat=page-range

Specify pages from the overlay/underlay that are repeated after
"from" pages have been exhausted. See qpdf --help=page-ranges
for help with the page range syntax.
)");
ap.addHelpTopic("attachments", "work with embedded files", R"(It is possible to list, add, or delete embedded files (also known
as attachments) and to copy attachments from other files. See help
on individual options for details. Run qpdf --help=add-attachment
for additional details about adding attachments.
)");
ap.addOptionHelp("--list-attachments", "attachments", "list embedded files", R"(Show the key and stream number for each embedded file. Combine
with --verbose for more detailed information.
)");
ap.addOptionHelp("--show-attachment", "attachments", "export an embedded file", R"(--show-attachment=key

Write the contents of the specified attachment to standard
output as binary data. Get the key with --list-attachments.
)");
ap.addOptionHelp("--add-attachment", "attachments", "start add attachment options", R"(--add-attachment file options --

The --add-attachment flag and its options may be repeated to add
multiple attachments. Run qpdf --help=add-attachment for details.
)");
ap.addOptionHelp("--remove-attachment", "attachments", "remove an embedded file", R"(--remove-attachment=key

Remove an embedded file using its key. Get the key with
--list-attachments.
)");
ap.addOptionHelp("--copy-attachments-from", "attachments", "start copy attachment options", R"(--copy-attachments-from file options --

The --copy-attachments-from flag and its options may be repeated
to copy attachments from multiple files. Run
qpdf --help=copy-attachments for details.
)");
}
static void add_help_6(QPDFArgParser& ap)
{
ap.addHelpTopic("pdf-dates", "PDF date format", R"(When a date is required, the date should conform to the PDF date
format specification, which is "D:yyyymmddhhmmssz" where "z" is
either literally upper case "Z" for UTC or a timezone offset in
the form "-hh'mm'" or "+hh'mm'". Negative timezone offsets indicate
time before UTC. Positive offsets indicate how far after. For
example, US Eastern Standard Time (America/New_York) is "-05'00'",
and Indian Standard Time (Asia/Calcutta) is "+05'30'".

Examples:
- D:20210207161528-05'00'   February 7, 2021 at 4:15:28 p.m.
- D:20210207211528Z         February 7, 2021 at 21:15:28 UTC
)");
ap.addHelpTopic("add-attachment", "attach (embed) files", R"(The options listed below appear between --add-attachment and its
terminating "--".
)");
ap.addOptionHelp("--key", "add-attachment", "specify attachment key", R"(--key=key

Specify the key to use for the attachment in the embedded files
table. It defaults to the last element of the attached file's
filename.
)");
ap.addOptionHelp("--filename", "add-attachment", "set attachment's displayed filename", R"(--filename=name

Specify the filename to be used for the attachment. This is what
is usually displayed to the user and is the name most graphical
PDF viewers will use when saving a file. It defaults to the last
element of the attached file's filename.
)");
ap.addOptionHelp("--creationdate", "add-attachment", "set attachment's creation date", R"(--creationdate=date

Specify the attachment's creation date in PDF format; defaults
to the current time. Run qpdf --help=pdf-dates for information
about the date format.
)");
ap.addOptionHelp("--moddate", "add-attachment", "set attachment's modification date", R"(--moddate=date

Specify the attachment's modification date in PDF format;
defaults to the current time. Run qpdf --help=pdf-dates for
information about the date format.
)");
ap.addOptionHelp("--mimetype", "add-attachment", "attachment mime type (e.g. application/pdf)", R"(--mimetype=type/subtype

Specify the mime type for the attachment, such as text/plain,
application/pdf, image/png, etc.
)");
ap.addOptionHelp("--description", "add-attachment", "set attachment's description", R"(--description="text"

Supply descriptive text for the attachment, displayed by some
PDF viewers.
)");
ap.addOptionHelp("--replace", "add-attachment", "replace attachment with same key", R"(Indicate that any existing attachment with the same key should
be replaced by the new attachment. Otherwise, qpdf gives an
error if an attachment with that key is already present.
)");
ap.addHelpTopic("copy-attachments", "copy attachments from another file", R"(The options listed below appear between --copy-attachments-from and
its terminating "--".

To copy attachments from a password-protected file, use
the --password option after the file name.
)");
ap.addOptionHelp("--prefix", "copy-attachments", "key prefix for copying attachments", R"(--prefix=prefix

Prepend a prefix to each key; may be needed if there are
duplicate attachment keys. This affects the key only, not the
file name.
)");
ap.addHelpTopic("inspection", "inspect PDF files", R"(These options provide tools for inspecting PDF files. When any of
the options in this section are specified, no output file should be
given.
)");
ap.addOptionHelp("--is-encrypted", "inspection", "silently test whether a file is encrypted", R"(Silently exit with a code indicating the file's encryption status:

0: the file is encrypted
1: not used
2: the file is not encrypted

This can be used with password-protected files even if you don't
know the password.
)");
ap.addOptionHelp("--requires-password", "inspection", "silently test a file's password", R"(Silently exit with a code indicating the file's password status:

0: a password, other than as supplied, is required
1: not used
2: the file is not encrypted
3: the file is encrypted, and correct password (if any) has been supplied
)");
ap.addOptionHelp("--check", "inspection", "partially check whether PDF is valid", R"(Check the structure of the PDF file as well as a number of other
aspects of the file, and write information about the file to
standard output. Note that qpdf does not perform any validation
of the actual PDF page content or semantic correctness of the
PDF file. It merely checks that the PDF file is syntactically
valid. See also qpdf --help=exit-status.
)");
ap.addOptionHelp("--show-encryption", "inspection", "information about encrypted files", R"(Show document encryption parameters. Also show the document's
user password if the owner password is given and the file was
encrypted using older encryption formats that allow user
password recovery.
)");
ap.addOptionHelp("--show-encryption-key", "inspection", "show key with --show-encryption", R"(When used with --show-encryption, causes the underlying
encryption key to be displayed.
)");
ap.addOptionHelp("--check-linearization", "inspection", "check linearization tables", R"(Check to see whether a file is linearized and, if so, whether
the linearization hint tables are correct.
)");
ap.addOptionHelp("--show-linearization", "inspection", "show linearization hint tables", R"(Check and display all data in the linearization hint tables.
)");
}
static void add_help_7(QPDFArgParser& ap)
{
ap.addOptionHelp("--show-xref", "inspection", "show cross reference data", R"(Show the contents of the cross-reference table or stream (object
locations in the file) in a human-readable form. This is
especially useful for files with cross-reference streams, which
are stored in a binary format.
)");
ap.addOptionHelp("--show-object", "inspection", "show contents of an object", R"(--show-object=trailer|obj[,gen]

Show the contents of the given object. This is especially useful
for inspecting objects that are inside of object streams (also
known as "compressed objects").
)");
ap.addOptionHelp("--raw-stream-data", "inspection", "show raw stream data", R"(When used with --show-object, if the object is a stream, write
the raw (compressed) binary stream data to standard output
instead of the object's contents. See also
--filtered-stream-data.
)");
ap.addOptionHelp("--filtered-stream-data", "inspection", "show filtered stream data", R"(When used with --show-object, if the object is a stream, write
the filtered (uncompressed, potentially binary) stream data to
standard output instead of the object's contents. See also
--raw-stream-data.
)");
ap.addOptionHelp("--show-npages", "inspection", "show number of pages", R"(Print the number of pages in the input file on a line by itself.
Useful for scripts.
)");
ap.addOptionHelp("--show-pages", "inspection", "display page dictionary information", R"(Show the object and generation number for each page dictionary
object and for each content stream associated with the page.
)");
ap.addOptionHelp("--with-images", "inspection", "include image details with --show-pages", R"(When used with --show-pages, also shows the object and
generation numbers for the image objects on each page.
)");
ap.addHelpTopic("json", "JSON output for PDF information", R"(Show information about the PDF file in JSON format. Please see the
JSON chapter in the qpdf manual for details.
)");
ap.addOptionHelp("--json", "json", "show file in json format", R"(Generate a JSON representation of the file. This is described in
depth in the JSON section of the manual.
)");
ap.addOptionHelp("--json-help", "json", "show format of json output", R"(Describe the format of the JSON output.
)");
ap.addOptionHelp("--json-key", "json", "restrict which keys are in json output", R"(--json-key=key

This option is repeatable. If given, only the specified
top-level keys will be included in the JSON output. Otherwise,
all keys will be included.
)");
ap.addOptionHelp("--json-object", "json", "restrict which objects are in JSON", R"(--json-object=trailer|obj[,gen]

This option is repeatable. If given, only specified objects will
be shown in the "objects" key of the JSON output. Otherwise, all
objects will be shown.
)");
ap.addHelpTopic("testing", "options for testing or debugging", R"(The options below are useful when writing automated test code that
includes files created by qpdf or when testing qpdf itself.
)");
ap.addOptionHelp("--static-id", "testing", "use a fixed document ID", R"(Use a fixed value for the document ID. This is intended for
testing only. Never use it for production files. See also
qpdf --help=--deterministic-id.
)");
ap.addOptionHelp("--static-aes-iv", "testing", "use a fixed AES vector", R"(Use a static initialization vector for AES-CBC. This is intended
for testing only so that output files can be reproducible. Never
use it for production files. This option is not secure since it
significantly weakens the encryption.
)");
ap.addOptionHelp("--linearize-pass1", "testing", "save pass 1 of linearization", R"(--linearize-pass1=file

Write the first pass of linearization to the named file. The
resulting file is not a valid PDF file. This option is useful only
for debugging qpdf.
)");
}
static void add_help(QPDFArgParser& ap)
{
    add_help_1(ap);
    add_help_2(ap);
    add_help_3(ap);
    add_help_4(ap);
    add_help_5(ap);
    add_help_6(ap);
    add_help_7(ap);
ap.addHelpFooter("For detailed help, visit the qpdf manual: https://qpdf.readthedocs.io\n");
}

