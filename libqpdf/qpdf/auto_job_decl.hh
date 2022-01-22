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
void argAllowWeakCrypto();
void argCheck();
void argCheckLinearization();
void argCoalesceContents();
void argCopyAttachmentsFrom();
void argDecrypt();
void argDeterministicId();
void argEmpty();
void argEncrypt();
void argExternalizeInlineImages();
void argFilteredStreamData();
void argFlattenRotation();
void argGenerateAppearances();
void argIgnoreXrefStreams();
void argIsEncrypted();
void argJson();
void argKeepInlineImages();
void argLinearize();
void argListAttachments();
void argNewlineBeforeEndstream();
void argNoOriginalObjectIds();
void argNoWarn();
void argOptimizeImages();
void argOverlay();
void argPages();
void argPasswordIsHexKey();
void argPreserveUnreferenced();
void argPreserveUnreferencedResources();
void argProgress();
void argQdf();
void argRawStreamData();
void argRecompressFlate();
void argRemovePageLabels();
void argReplaceInput();
void argRequiresPassword();
void argShowEncryption();
void argShowEncryptionKey();
void argShowLinearization();
void argShowNpages();
void argShowPages();
void argShowXref();
void argStaticAesIv();
void argStaticId();
void argSuppressPasswordRecovery();
void argSuppressRecovery();
void argUnderlay();
void argVerbose();
void argWarningExit0();
void argWithImages();
void argCollate(char *);
void argSplitPages(char *);
void argCompressionLevel(char *);
void argCopyEncryption(char *);
void argEncryptionFilePassword(char *);
void argForceVersion(char *);
void argIiMinBytes(char *);
void argJobJsonFile(char *);
void argJsonObject(char *);
void argKeepFilesOpenThreshold(char *);
void argLinearizePass1(char *);
void argMinVersion(char *);
void argOiMinArea(char *);
void argOiMinHeight(char *);
void argOiMinWidth(char *);
void argPassword(char *);
void argPasswordFile(char *);
void argRemoveAttachment(char *);
void argRotate(char *);
void argShowAttachment(char *);
void argShowObject(char *);
void argCompressStreams(char *);
void argDecodeLevel(char *);
void argFlattenAnnotations(char *);
void argJsonKey(char *);
void argKeepFilesOpen(char *);
void argNormalizeContent(char *);
void argObjectStreams(char *);
void argPasswordMode(char *);
void argRemoveUnreferencedResources(char *);
void argStreamData(char *);
void argPagesPositional(char*);
void argPagesPassword(char *);
void argEndPages();
void argEncPositional(char*);
void argEndEncryption();
void argEnc40Extract(char *);
void argEnc40Annotate(char *);
void argEnc40Print(char *);
void argEnc40Modify(char *);
void argEnd40BitEncryption();
void argEnc128CleartextMetadata();
void argEnc128ForceV4();
void argEnc128Accessibility(char *);
void argEnc128Extract(char *);
void argEnc128Print(char *);
void argEnc128Assemble(char *);
void argEnc128Annotate(char *);
void argEnc128Form(char *);
void argEnc128ModifyOther(char *);
void argEnc128Modify(char *);
void argEnc128UseAes(char *);
void argEnd128BitEncryption();
void argEnc256ForceR5();
void argEnc256AllowInsecure();
void argEnd256BitEncryption();
void argUOPositional(char*);
void argUOTo(char *);
void argUOFrom(char *);
void argUORepeat(char *);
void argUOPassword(char *);
void argEndUnderlayOverlay();
void argAttPositional(char*);
void argAttReplace();
void argAttKey(char *);
void argAttFilename(char *);
void argAttCreationdate(char *);
void argAttModdate(char *);
void argAttMimetype(char *);
void argAttDescription(char *);
void argEndAttachment();
void argCopyAttPositional(char*);
void argCopyAttPrefix(char *);
void argCopyAttPassword(char *);
void argEndCopyAttachment();
