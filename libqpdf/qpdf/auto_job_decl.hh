//
// This file is automatically generated by generate_auto_job.
// Edits will be automatically overwritten if the build is
// run in maintainer mode.
//
static constexpr char const* O_PAGES = "pages";
static constexpr char const* O_ENCRYPTION = "encryption";
static constexpr char const* O_40_BIT_ENCRYPTION = "40-bit encryption";
static constexpr char const* O_128_BIT_ENCRYPTION = "128-bit encryption";
static constexpr char const* O_256_BIT_ENCRYPTION = "256-bit encryption";
static constexpr char const* O_UNDERLAY_OVERLAY = "underlay/overlay";
static constexpr char const* O_ATTACHMENT = "attachment";
static constexpr char const* O_COPY_ATTACHMENT = "copy attachment";

void argVersion();
void argCopyright();
void argJsonHelp();
void argShowCrypto();
void argJobJsonHelp();
void argPositional(char*);
void argAddAttachment();
void argCopyAttachmentsFrom();
void argEncrypt();
void argOverlay();
void argPages();
void argUnderlay();
void argPagesPositional(char*);
void argPagesPassword(char *);
void argEndPages();
void argEncPositional(char*);
void argEndEncryption();
void argEnd40BitEncryption();
void argEnd128BitEncryption();
void argEnd256BitEncryption();
void argUOPositional(char*);
void argEndUnderlayOverlay();
void argAttPositional(char*);
void argEndAttachment();
void argCopyAttPositional(char*);
void argEndCopyAttachment();
