#include <qpdf/QPDFJob.hh>

// See "HOW TO ADD A COMMAND-LINE ARGUMENT" in README-maintainer.

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <cstdio>
#include <ctype.h>
#include <memory>

#include <qpdf/QUtil.hh>
#include <qpdf/QTC.hh>
#include <qpdf/QPDFCryptoProvider.hh>
#include <qpdf/QPDFArgParser.hh>
#include <qpdf/QPDFJob.hh>
#include <qpdf/QIntC.hh>

namespace
{
    class ArgParser
    {
      public:
        ArgParser(QPDFArgParser& ap, QPDFJob& o);
        void parseOptions();

      private:
#       include <qpdf/auto_job_decl.hh>

        void usage(std::string const& message);
        void initOptionTables();
        void doFinalChecks();
        void parseUnderOverlayOptions(QPDFJob::UnderOverlay*);
        void parseRotationParameter(std::string const&);
        std::vector<int> parseNumrange(char const* range, int max,
                                       bool throw_error = false);

        QPDFArgParser ap;
        QPDFJob& o;
        std::vector<char*> accumulated_args; // points to member in ap
        char* pages_password;
    };
}

ArgParser::ArgParser(QPDFArgParser& ap, QPDFJob& o) :
    ap(ap),
    o(o),
    pages_password(nullptr)
{
    initOptionTables();
}

#include <qpdf/auto_job_help.hh>

void
ArgParser::initOptionTables()
{

#   include <qpdf/auto_job_init.hh>
    this->ap.addFinalCheck(
        QPDFArgParser::bindBare(&ArgParser::doFinalChecks, this));
    // add_help is defined in auto_job_help.hh
    add_help(this->ap);
}

void
ArgParser::argPositional(char* arg)
{
    if (o.infilename == 0)
    {
        o.infilename = QUtil::make_shared_cstr(arg);
    }
    else if (o.outfilename == 0)
    {
        o.outfilename = QUtil::make_shared_cstr(arg);
    }
    else
    {
        usage(std::string("unknown argument ") + arg);
    }
}

void
ArgParser::argVersion()
{
    auto whoami = this->ap.getProgname();
    std::cout
        << whoami << " version " << QPDF::QPDFVersion() << std::endl
        << "Run " << whoami << " --copyright to see copyright and license information."
        << std::endl;
}

void
ArgParser::argCopyright()
{
    // Make sure the output looks right on an 80-column display.
    //               1         2         3         4         5         6         7         8
    //      12345678901234567890123456789012345678901234567890123456789012345678901234567890
    std::cout
        << this->ap.getProgname()
        << " version " << QPDF::QPDFVersion() << std::endl
        << std::endl
        << "Copyright (c) 2005-2021 Jay Berkenbilt"
        << std::endl
        << "QPDF is licensed under the Apache License, Version 2.0 (the \"License\");"
        << std::endl
        << "you may not use this file except in compliance with the License."
        << std::endl
        << "You may obtain a copy of the License at"
        << std::endl
        << std::endl
        << "  http://www.apache.org/licenses/LICENSE-2.0"
        << std::endl
        << std::endl
        << "Unless required by applicable law or agreed to in writing, software"
        << std::endl
        << "distributed under the License is distributed on an \"AS IS\" BASIS,"
        << std::endl
        << "WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied."
        << std::endl
        << "See the License for the specific language governing permissions and"
        << std::endl
        << "limitations under the License."
        << std::endl
        << std::endl
        << "Versions of qpdf prior to version 7 were released under the terms"
        << std::endl
        << "of version 2.0 of the Artistic License. At your option, you may"
        << std::endl
        << "continue to consider qpdf to be licensed under those terms. Please"
        << std::endl
        << "see the manual for additional information."
        << std::endl;
}

void
ArgParser::argJsonHelp()
{
    // Make sure the output looks right on an 80-column display.
    //               1         2         3         4         5         6         7         8
    //      12345678901234567890123456789012345678901234567890123456789012345678901234567890
    std::cout
        << "The json block below contains the same structure with the same keys as the"
        << std::endl
        << "json generated by qpdf. In the block below, the values are descriptions of"
        << std::endl
        << "the meanings of those entries. The specific contract guaranteed by qpdf in"
        << std::endl
        << "its json representation is explained in more detail in the manual. You can"
        << std::endl
        << "specify a subset of top-level keys when you invoke qpdf, but the \"version\""
        << std::endl
        << "and \"parameters\" keys will always be present. Note that the \"encrypt\""
        << std::endl
        << "key's values will be populated for non-encrypted files. Some values will"
        << std::endl
        << "be null, and others will have values that apply to unencrypted files."
        << std::endl
        << QPDFJob::json_schema().unparse()
        << std::endl;
}

void
ArgParser::argShowCrypto()
{
    auto crypto = QPDFCryptoProvider::getRegisteredImpls();
    std::string default_crypto = QPDFCryptoProvider::getDefaultProvider();
    std::cout << default_crypto << std::endl;
    for (auto const& iter: crypto)
    {
        if (iter != default_crypto)
        {
            std::cout << iter << std::endl;
        }
    }
}

void
ArgParser::argPassword(char* parameter)
{
    o.password = QUtil::make_shared_cstr(parameter);
}

void
ArgParser::argPasswordFile(char* parameter)
{
    std::list<std::string> lines;
    if (strcmp(parameter, "-") == 0)
    {
        QTC::TC("qpdf", "qpdf password stdin");
        lines = QUtil::read_lines_from_file(std::cin);
    }
    else
    {
        QTC::TC("qpdf", "qpdf password file");
        lines = QUtil::read_lines_from_file(parameter);
    }
    if (lines.size() >= 1)
    {
        o.password = QUtil::make_shared_cstr(lines.front());

        if (lines.size() > 1)
        {
            std::cerr << this->ap.getProgname()
                      << ": WARNING: all but the first line of"
                      << " the password file are ignored" << std::endl;
        }
    }
}

void
ArgParser::argEmpty()
{
    o.infilename = QUtil::make_shared_cstr("");
}

void
ArgParser::argLinearize()
{
    o.linearize = true;
}

void
ArgParser::argEncrypt()
{
    this->accumulated_args.clear();
    if (this->ap.isCompleting() && this->ap.argsLeft() == 0)
    {
        this->ap.insertCompletion("user-password");
    }
    this->ap.selectOptionTable(O_ENCRYPTION);
}

void
ArgParser::argEncPositional(char* arg)
{
    this->accumulated_args.push_back(arg);
    size_t n_args = this->accumulated_args.size();
    if (n_args < 3)
    {
        if (this->ap.isCompleting() && (this->ap.argsLeft() == 0))
        {
            if (n_args == 1)
            {
                this->ap.insertCompletion("owner-password");
            }
            else if (n_args == 2)
            {
                this->ap.insertCompletion("40");
                this->ap.insertCompletion("128");
                this->ap.insertCompletion("256");
            }
        }
        return;
    }
    o.user_password = this->accumulated_args.at(0);
    o.owner_password = this->accumulated_args.at(1);
    std::string len_str = this->accumulated_args.at(2);
    if (len_str == "40")
    {
        o.keylen = 40;
        this->ap.selectOptionTable(O_40_BIT_ENCRYPTION);
    }
    else if (len_str == "128")
    {
        o.keylen = 128;
        this->ap.selectOptionTable(O_128_BIT_ENCRYPTION);
    }
    else if (len_str == "256")
    {
        o.keylen = 256;
        o.use_aes = true;
        this->ap.selectOptionTable(O_256_BIT_ENCRYPTION);
    }
    else
    {
        usage("encryption key length must be 40, 128, or 256");
    }
}

void
ArgParser::argDecrypt()
{
    o.decrypt = true;
    o.encrypt = false;
    o.copy_encryption = false;
}

void
ArgParser::argPasswordIsHexKey()
{
    o.password_is_hex_key = true;
}

void
ArgParser::argSuppressPasswordRecovery()
{
    o.suppress_password_recovery = true;
}

void
ArgParser::argPasswordMode(char* parameter)
{
    if (strcmp(parameter, "bytes") == 0)
    {
        o.password_mode = QPDFJob::pm_bytes;
    }
    else if (strcmp(parameter, "hex-bytes") == 0)
    {
        o.password_mode = QPDFJob::pm_hex_bytes;
    }
    else if (strcmp(parameter, "unicode") == 0)
    {
        o.password_mode = QPDFJob::pm_unicode;
    }
    else if (strcmp(parameter, "auto") == 0)
    {
        o.password_mode = QPDFJob::pm_auto;
    }
    else
    {
        usage("invalid password-mode option");
    }
}

void
ArgParser::argEnc256AllowInsecure()
{
    o.allow_insecure = true;
}

void
ArgParser::argAllowWeakCrypto()
{
    o.allow_weak_crypto = true;
}

void
ArgParser::argCopyEncryption(char* parameter)
{
    o.encryption_file = parameter;
    o.copy_encryption = true;
    o.encrypt = false;
    o.decrypt = false;
}

void
ArgParser::argEncryptionFilePassword(char* parameter)
{
    o.encryption_file_password = QUtil::make_shared_cstr(parameter);
}

void
ArgParser::argCollate(char* parameter)
{
    auto n = ((parameter == 0) ? 1 :
              QUtil::string_to_uint(parameter));
    o.collate = QIntC::to_size(n);
}

void
ArgParser::argPages()
{
    if (! o.page_specs.empty())
    {
        usage("the --pages may only be specified one time");
    }
    this->accumulated_args.clear();
    this->ap.selectOptionTable(O_PAGES);
}

void
ArgParser::argPagesPassword(char* parameter)
{
    if (this->pages_password != nullptr)
    {
        QTC::TC("qpdf", "qpdf duplicated pages password");
        usage("--password already specified for this file");
    }
    if (this->accumulated_args.size() != 1)
    {
        QTC::TC("qpdf", "qpdf misplaced pages password");
        usage("in --pages, --password must immediately follow a file name");
    }
    this->pages_password = parameter;
}

void
ArgParser::argPagesPositional(char* arg)
{
    if (arg == nullptr)
    {
        if (this->accumulated_args.empty())
        {
            return;
        }
    }
    else
    {
        this->accumulated_args.push_back(arg);
    }

    char const* file = this->accumulated_args.at(0);
    char const* range = nullptr;

    size_t n_args = this->accumulated_args.size();
    if (n_args >= 2)
    {
        range = this->accumulated_args.at(1);
    }

    // See if the user omitted the range entirely, in which case we
    // assume "1-z".
    char* next_file = nullptr;
    if (range == nullptr)
    {
        if (arg == nullptr)
        {
            // The filename or password was the last argument
            QTC::TC("qpdf", "qpdf pages range omitted at end",
                    this->pages_password == nullptr ? 0 : 1);
        }
        else
        {
            // We need to accumulate some more arguments
            return;
        }
    }
    else
    {
        try
        {
            parseNumrange(range, 0, true);
        }
        catch (std::runtime_error& e1)
        {
            // The range is invalid.  Let's see if it's a file.
            if (strcmp(range, ".") == 0)
            {
                // "." means the input file.
                QTC::TC("qpdf", "qpdf pages range omitted with .");
            }
            else if (QUtil::file_can_be_opened(range))
            {
                QTC::TC("qpdf", "qpdf pages range omitted in middle");
                // Yup, it's a file.
            }
            else
            {
                // Give the range error
                usage(e1.what());
            }
            next_file = const_cast<char*>(range);
            range = nullptr;
        }
    }
    if (range == nullptr)
    {
        range = "1-z";
    }
    o.page_specs.push_back(QPDFJob::PageSpec(file, this->pages_password, range));
    this->accumulated_args.clear();
    this->pages_password = nullptr;
    if (next_file != nullptr)
    {
        this->accumulated_args.push_back(next_file);
    }
}

void
ArgParser::argEndPages()
{
    argPagesPositional(nullptr);
    if (o.page_specs.empty())
    {
        usage("--pages: no page specifications given");
    }
}

void
ArgParser::argUnderlay()
{
    parseUnderOverlayOptions(&o.underlay);
}

void
ArgParser::argOverlay()
{
    parseUnderOverlayOptions(&o.overlay);
}

void
ArgParser::argRotate(char* parameter)
{
    parseRotationParameter(parameter);
}

void
ArgParser::argFlattenRotation()
{
    o.flatten_rotation = true;
}

void
ArgParser::argListAttachments()
{
    o.list_attachments = true;
    o.require_outfile = false;
}

void
ArgParser::argShowAttachment(char* parameter)
{
    o.attachment_to_show = parameter;
    o.require_outfile = false;
}

void
ArgParser::argRemoveAttachment(char* parameter)
{
    o.attachments_to_remove.push_back(parameter);
}

void
ArgParser::argAddAttachment()
{
    o.attachments_to_add.push_back(QPDFJob::AddAttachment());
    this->ap.selectOptionTable(O_ATTACHMENT);
}

void
ArgParser::argCopyAttachmentsFrom()
{
    o.attachments_to_copy.push_back(QPDFJob::CopyAttachmentFrom());
    this->ap.selectOptionTable(O_COPY_ATTACHMENT);
}

void
ArgParser::argStreamData(char* parameter)
{
    o.stream_data_set = true;
    if (strcmp(parameter, "compress") == 0)
    {
        o.stream_data_mode = qpdf_s_compress;
    }
    else if (strcmp(parameter, "preserve") == 0)
    {
        o.stream_data_mode = qpdf_s_preserve;
    }
    else if (strcmp(parameter, "uncompress") == 0)
    {
        o.stream_data_mode = qpdf_s_uncompress;
    }
    else
    {
        // If this happens, it means streamDataChoices in
        // ArgParser::initOptionTable is wrong.
        usage("invalid stream-data option");
    }
}

void
ArgParser::argCompressStreams(char* parameter)
{
    o.compress_streams_set = true;
    o.compress_streams = (strcmp(parameter, "y") == 0);
}

void
ArgParser::argRecompressFlate()
{
    o.recompress_flate_set = true;
    o.recompress_flate = true;
}

void
ArgParser::argCompressionLevel(char* parameter)
{
    o.compression_level = QUtil::string_to_int(parameter);
}

void
ArgParser::argDecodeLevel(char* parameter)
{
    o.decode_level_set = true;
    if (strcmp(parameter, "none") == 0)
    {
        o.decode_level = qpdf_dl_none;
    }
    else if (strcmp(parameter, "generalized") == 0)
    {
        o.decode_level = qpdf_dl_generalized;
    }
    else if (strcmp(parameter, "specialized") == 0)
    {
        o.decode_level = qpdf_dl_specialized;
    }
    else if (strcmp(parameter, "all") == 0)
    {
        o.decode_level = qpdf_dl_all;
    }
    else
    {
        // If this happens, it means decodeLevelChoices in
        // ArgParser::initOptionTable is wrong.
        usage("invalid option");
    }
}

void
ArgParser::argNormalizeContent(char* parameter)
{
    o.normalize_set = true;
    o.normalize = (strcmp(parameter, "y") == 0);
}

void
ArgParser::argSuppressRecovery()
{
    o.suppress_recovery = true;
}

void
ArgParser::argObjectStreams(char* parameter)
{
    o.object_stream_set = true;
    if (strcmp(parameter, "disable") == 0)
    {
        o.object_stream_mode = qpdf_o_disable;
    }
    else if (strcmp(parameter, "preserve") == 0)
    {
        o.object_stream_mode = qpdf_o_preserve;
    }
    else if (strcmp(parameter, "generate") == 0)
    {
        o.object_stream_mode = qpdf_o_generate;
    }
    else
    {
        // If this happens, it means objectStreamsChoices in
        // ArgParser::initOptionTable is wrong.
        usage("invalid object stream mode");
    }
}

void
ArgParser::argIgnoreXrefStreams()
{
    o.ignore_xref_streams = true;
}

void
ArgParser::argQdf()
{
    o.qdf_mode = true;
}

void
ArgParser::argPreserveUnreferenced()
{
    o.preserve_unreferenced_objects = true;
}

void
ArgParser::argPreserveUnreferencedResources()
{
    o.remove_unreferenced_page_resources = QPDFJob::re_no;
}

void
ArgParser::argRemoveUnreferencedResources(char* parameter)
{
    if (strcmp(parameter, "auto") == 0)
    {
        o.remove_unreferenced_page_resources = QPDFJob::re_auto;
    }
    else if (strcmp(parameter, "yes") == 0)
    {
        o.remove_unreferenced_page_resources = QPDFJob::re_yes;
    }
    else if (strcmp(parameter, "no") == 0)
    {
        o.remove_unreferenced_page_resources = QPDFJob::re_no;
    }
    else
    {
        // If this happens, it means remove_unref_choices in
        // ArgParser::initOptionTable is wrong.
        usage("invalid value for --remove-unreferenced-page-resources");
    }
}

void
ArgParser::argKeepFilesOpen(char* parameter)
{
    o.keep_files_open_set = true;
    o.keep_files_open = (strcmp(parameter, "y") == 0);
}

void
ArgParser::argKeepFilesOpenThreshold(char* parameter)
{
    o.keep_files_open_threshold = QUtil::string_to_uint(parameter);
}

void
ArgParser::argNewlineBeforeEndstream()
{
    o.newline_before_endstream = true;
}

void
ArgParser::argLinearizePass1(char* parameter)
{
    o.linearize_pass1 = parameter;
}

void
ArgParser::argCoalesceContents()
{
    o.coalesce_contents = true;
}

void
ArgParser::argFlattenAnnotations(char* parameter)
{
    o.flatten_annotations = true;
    if (strcmp(parameter, "screen") == 0)
    {
        o.flatten_annotations_forbidden |= an_no_view;
    }
    else if (strcmp(parameter, "print") == 0)
    {
        o.flatten_annotations_required |= an_print;
    }
}

void
ArgParser::argGenerateAppearances()
{
    o.generate_appearances = true;
}

void
ArgParser::argMinVersion(char* parameter)
{
    o.min_version = parameter;
}

void
ArgParser::argForceVersion(char* parameter)
{
    o.force_version = parameter;
}

void
ArgParser::argSplitPages(char* parameter)
{
    int n = ((parameter == 0) ? 1 :
             QUtil::string_to_int(parameter));
    o.split_pages = n;
}

void
ArgParser::argVerbose()
{
    o.verbose = true;
}

void
ArgParser::argProgress()
{
    o.progress = true;
}

void
ArgParser::argNoWarn()
{
    o.suppress_warnings = true;
}

void
ArgParser::argWarningExit0()
{
    o.warnings_exit_zero = true;
}

void
ArgParser::argDeterministicId()
{
    o.deterministic_id = true;
}

void
ArgParser::argStaticId()
{
    o.static_id = true;
}

void
ArgParser::argStaticAesIv()
{
    o.static_aes_iv = true;
}

void
ArgParser::argNoOriginalObjectIds()
{
    o.suppress_original_object_id = true;
}

void
ArgParser::argShowEncryption()
{
    o.show_encryption = true;
    o.require_outfile = false;
}

void
ArgParser::argShowEncryptionKey()
{
    o.show_encryption_key = true;
}

void
ArgParser::argCheckLinearization()
{
    o.check_linearization = true;
    o.require_outfile = false;
}

void
ArgParser::argShowLinearization()
{
    o.show_linearization = true;
    o.require_outfile = false;
}

void
ArgParser::argShowXref()
{
    o.show_xref = true;
    o.require_outfile = false;
}

void
ArgParser::argShowObject(char* parameter)
{
    QPDFJob::parse_object_id(parameter, o.show_trailer, o.show_obj, o.show_gen);
    o.require_outfile = false;
}

void
ArgParser::argRawStreamData()
{
    o.show_raw_stream_data = true;
}

void
ArgParser::argFilteredStreamData()
{
    o.show_filtered_stream_data = true;
}

void
ArgParser::argShowNpages()
{
    o.show_npages = true;
    o.require_outfile = false;
}

void
ArgParser::argShowPages()
{
    o.show_pages = true;
    o.require_outfile = false;
}

void
ArgParser::argWithImages()
{
    o.show_page_images = true;
}

void
ArgParser::argJson()
{
    o.json = true;
    o.require_outfile = false;
}

void
ArgParser::argJsonKey(char* parameter)
{
    o.json_keys.insert(parameter);
}

void
ArgParser::argJsonObject(char* parameter)
{
    o.json_objects.insert(parameter);
}

void
ArgParser::argCheck()
{
    o.check = true;
    o.require_outfile = false;
}

void
ArgParser::argOptimizeImages()
{
    o.optimize_images = true;
}

void
ArgParser::argExternalizeInlineImages()
{
    o.externalize_inline_images = true;
}

void
ArgParser::argKeepInlineImages()
{
    o.keep_inline_images = true;
}

void
ArgParser::argRemovePageLabels()
{
    o.remove_page_labels = true;
}

void
ArgParser::argOiMinWidth(char* parameter)
{
    o.oi_min_width = QUtil::string_to_uint(parameter);
}

void
ArgParser::argOiMinHeight(char* parameter)
{
    o.oi_min_height = QUtil::string_to_uint(parameter);
}

void
ArgParser::argOiMinArea(char* parameter)
{
    o.oi_min_area = QUtil::string_to_uint(parameter);
}

void
ArgParser::argIiMinBytes(char* parameter)
{
    o.ii_min_bytes = QUtil::string_to_uint(parameter);
}

void
ArgParser::argEnc40Print(char* parameter)
{
    o.r2_print = (strcmp(parameter, "y") == 0);
}

void
ArgParser::argEnc40Modify(char* parameter)
{
    o.r2_modify = (strcmp(parameter, "y") == 0);
}

void
ArgParser::argEnc40Extract(char* parameter)
{
    o.r2_extract = (strcmp(parameter, "y") == 0);
}

void
ArgParser::argEnc40Annotate(char* parameter)
{
    o.r2_annotate = (strcmp(parameter, "y") == 0);
}

void
ArgParser::argEnc128Accessibility(char* parameter)
{
    o.r3_accessibility = (strcmp(parameter, "y") == 0);
}

void
ArgParser::argEnc128Extract(char* parameter)
{
    o.r3_extract = (strcmp(parameter, "y") == 0);
}

void
ArgParser::argEnc128Print(char* parameter)
{
    if (strcmp(parameter, "full") == 0)
    {
        o.r3_print = qpdf_r3p_full;
    }
    else if (strcmp(parameter, "low") == 0)
    {
        o.r3_print = qpdf_r3p_low;
    }
    else if (strcmp(parameter, "none") == 0)
    {
        o.r3_print = qpdf_r3p_none;
    }
    else
    {
        usage("invalid print option");
    }
}

void
ArgParser::argEnc128Modify(char* parameter)
{
    if (strcmp(parameter, "all") == 0)
    {
        o.r3_assemble = true;
        o.r3_annotate_and_form = true;
        o.r3_form_filling = true;
        o.r3_modify_other = true;
    }
    else if (strcmp(parameter, "annotate") == 0)
    {
        o.r3_assemble = true;
        o.r3_annotate_and_form = true;
        o.r3_form_filling = true;
        o.r3_modify_other = false;
    }
    else if (strcmp(parameter, "form") == 0)
    {
        o.r3_assemble = true;
        o.r3_annotate_and_form = false;
        o.r3_form_filling = true;
        o.r3_modify_other = false;
    }
    else if (strcmp(parameter, "assembly") == 0)
    {
        o.r3_assemble = true;
        o.r3_annotate_and_form = false;
        o.r3_form_filling = false;
        o.r3_modify_other = false;
    }
    else if (strcmp(parameter, "none") == 0)
    {
        o.r3_assemble = false;
        o.r3_annotate_and_form = false;
        o.r3_form_filling = false;
        o.r3_modify_other = false;
    }
    else
    {
        usage("invalid modify option");
    }
}

void
ArgParser::argEnc128CleartextMetadata()
{
    o.cleartext_metadata = true;
}

void
ArgParser::argEnc128Assemble(char* parameter)
{
    o.r3_assemble = (strcmp(parameter, "y") == 0);
}

void
ArgParser::argEnc128Annotate(char* parameter)
{
    o.r3_annotate_and_form = (strcmp(parameter, "y") == 0);
}

void
ArgParser::argEnc128Form(char* parameter)
{
    o.r3_form_filling = (strcmp(parameter, "y") == 0);
}

void
ArgParser::argEnc128ModifyOther(char* parameter)
{
    o.r3_modify_other = (strcmp(parameter, "y") == 0);
}

void
ArgParser::argEnc128UseAes(char* parameter)
{
    o.use_aes = (strcmp(parameter, "y") == 0);
}

void
ArgParser::argEnc128ForceV4()
{
    o.force_V4 = true;
}

void
ArgParser::argEnc256ForceR5()
{
    o.force_R5 = true;
}

void
ArgParser::argEndEncryption()
{
    o.encrypt = true;
    o.decrypt = false;
    o.copy_encryption = false;
}

void
ArgParser::argEnd40BitEncryption()
{
    argEndEncryption();
}

void
ArgParser::argEnd128BitEncryption()
{
    argEndEncryption();
}

void
ArgParser::argEnd256BitEncryption()
{
    argEndEncryption();
}

void
ArgParser::argUOPositional(char* arg)
{
    if (! o.under_overlay->filename.empty())
    {
        usage(o.under_overlay->which + " file already specified");
    }
    else
    {
        o.under_overlay->filename = arg;
    }
}

void
ArgParser::argUOTo(char* parameter)
{
    parseNumrange(parameter, 0);
    o.under_overlay->to_nr = parameter;
}

void
ArgParser::argUOFrom(char* parameter)
{
    if (strlen(parameter))
    {
        parseNumrange(parameter, 0);
    }
    o.under_overlay->from_nr = parameter;
}

void
ArgParser::argUORepeat(char* parameter)
{
    if (strlen(parameter))
    {
        parseNumrange(parameter, 0);
    }
    o.under_overlay->repeat_nr = parameter;
}

void
ArgParser::argUOPassword(char* parameter)
{
    o.under_overlay->password = QUtil::make_shared_cstr(parameter);
}

void
ArgParser::argEndUnderlayOverlay()
{
    if (o.under_overlay->filename.empty())
    {
        usage(o.under_overlay->which + " file not specified");
    }
    o.under_overlay = 0;
}

void
ArgParser::argReplaceInput()
{
    o.replace_input = true;
}

void
ArgParser::argIsEncrypted()
{
    o.check_is_encrypted = true;
    o.require_outfile = false;
}

void
ArgParser::argRequiresPassword()
{
    o.check_requires_password = true;
    o.require_outfile = false;
}

void
ArgParser::argAttPositional(char* arg)
{
    o.attachments_to_add.back().path = arg;
}

void
ArgParser::argAttKey(char* parameter)
{
    o.attachments_to_add.back().key = parameter;
}

void
ArgParser::argAttFilename(char* parameter)
{
    o.attachments_to_add.back().filename = parameter;
}

void
ArgParser::argAttCreationdate(char* parameter)
{
    if (! QUtil::pdf_time_to_qpdf_time(parameter))
    {
        usage(std::string(parameter) + " is not a valid PDF timestamp");
    }
    o.attachments_to_add.back().creationdate = parameter;
}

void
ArgParser::argAttModdate(char* parameter)
{
    if (! QUtil::pdf_time_to_qpdf_time(parameter))
    {
        usage(std::string(parameter) + " is not a valid PDF timestamp");
    }
    o.attachments_to_add.back().moddate = parameter;
}

void
ArgParser::argAttMimetype(char* parameter)
{
    if (strchr(parameter, '/') == nullptr)
    {
        usage("mime type should be specified as type/subtype");
    }
    o.attachments_to_add.back().mimetype = parameter;
}

void
ArgParser::argAttDescription(char* parameter)
{
    o.attachments_to_add.back().description = parameter;
}

void
ArgParser::argAttReplace()
{
    o.attachments_to_add.back().replace = true;
}

void
ArgParser::argEndAttachment()
{
    static std::string now = QUtil::qpdf_time_to_pdf_time(
        QUtil::get_current_qpdf_time());
    auto& cur = o.attachments_to_add.back();
    if (cur.path.empty())
    {
        usage("add attachment: no path specified");
    }
    std::string last_element = QUtil::path_basename(cur.path);
    if (last_element.empty())
    {
        usage("path for --add-attachment may not be empty");
    }
    if (cur.filename.empty())
    {
        cur.filename = last_element;
    }
    if (cur.key.empty())
    {
        cur.key = last_element;
    }
    if (cur.creationdate.empty())
    {
        cur.creationdate = now;
    }
    if (cur.moddate.empty())
    {
        cur.moddate = now;
    }
}

void
ArgParser::argCopyAttPositional(char* arg)
{
    o.attachments_to_copy.back().path = arg;
}

void
ArgParser::argCopyAttPrefix(char* parameter)
{
    o.attachments_to_copy.back().prefix = parameter;
}

void
ArgParser::argCopyAttPassword(char* parameter)
{
    o.attachments_to_copy.back().password = parameter;
}

void
ArgParser::argEndCopyAttachment()
{
    if (o.attachments_to_copy.back().path.empty())
    {
        usage("copy attachments: no path specified");
    }
}

void
ArgParser::usage(std::string const& message)
{
    this->ap.usage(message);
}

std::vector<int>
ArgParser::parseNumrange(char const* range, int max, bool throw_error)
{
    try
    {
        return QUtil::parse_numrange(range, max);
    }
    catch (std::runtime_error& e)
    {
        if (throw_error)
        {
            throw(e);
        }
        else
        {
            usage(e.what());
        }
    }
    return std::vector<int>();
}

void
ArgParser::parseUnderOverlayOptions(QPDFJob::UnderOverlay* uo)
{
    o.under_overlay = uo;
    this->ap.selectOptionTable(O_UNDERLAY_OVERLAY);
}

void
ArgParser::parseRotationParameter(std::string const& parameter)
{
    std::string angle_str;
    std::string range;
    size_t colon = parameter.find(':');
    int relative = 0;
    if (colon != std::string::npos)
    {
        if (colon > 0)
        {
            angle_str = parameter.substr(0, colon);
        }
        if (colon + 1 < parameter.length())
        {
            range = parameter.substr(colon + 1);
        }
    }
    else
    {
        angle_str = parameter;
    }
    if (angle_str.length() > 0)
    {
        char first = angle_str.at(0);
        if ((first == '+') || (first == '-'))
        {
            relative = ((first == '+') ? 1 : -1);
            angle_str = angle_str.substr(1);
        }
        else if (! QUtil::is_digit(angle_str.at(0)))
        {
            angle_str = "";
        }
    }
    if (range.empty())
    {
        range = "1-z";
    }
    bool range_valid = false;
    try
    {
        parseNumrange(range.c_str(), 0, true);
        range_valid = true;
    }
    catch (std::runtime_error const&)
    {
        // ignore
    }
    if (range_valid &&
        ((angle_str == "0") ||(angle_str == "90") ||
         (angle_str == "180") || (angle_str == "270")))
    {
        int angle = QUtil::string_to_int(angle_str.c_str());
        if (relative == -1)
        {
            angle = -angle;
        }
        o.rotations[range] = QPDFJob::RotationSpec(angle, (relative != 0));
    }
    else
    {
        usage("invalid parameter to rotate: " + parameter);
    }
}

void
ArgParser::parseOptions()
{
    try
    {
        this->ap.parseArgs();
    }
    catch (QPDFArgParser::Usage& e)
    {
        usage(e.what());
    }
}

void
ArgParser::doFinalChecks()
{
    if (o.replace_input)
    {
        if (o.outfilename)
        {
            usage("--replace-input may not be used when"
                  " an output file is specified");
        }
        else if (o.split_pages)
        {
            usage("--split-pages may not be used with --replace-input");
        }
    }
    if (o.infilename == 0)
    {
        usage("an input file name is required");
    }
    else if (o.require_outfile && (o.outfilename == 0) && (! o.replace_input))
    {
        usage("an output file name is required; use - for standard output");
    }
    else if ((! o.require_outfile) &&
             ((o.outfilename != 0) || o.replace_input))
    {
        usage("no output file may be given for this option");
    }
    if (o.check_requires_password && o.check_is_encrypted)
    {
        usage("--requires-password and --is-encrypted may not be given"
              " together");
    }

    if (o.encrypt && (! o.allow_insecure) &&
        (o.owner_password.empty() &&
         (! o.user_password.empty()) &&
         (o.keylen == 256)))
    {
        // Note that empty owner passwords for R < 5 are copied from
        // the user password, so this lack of security is not an issue
        // for those files. Also we are consider only the ability to
        // open the file without a password to be insecure. We are not
        // concerned about whether the viewer enforces security
        // settings when the user and owner password match.
        usage("A PDF with a non-empty user password and an empty owner"
              " password encrypted with a 256-bit key is insecure as it"
              " can be opened without a password. If you really want to"
              " do this, you must also give the --allow-insecure option"
              " before the -- that follows --encrypt.");
    }

    if (o.require_outfile && o.outfilename &&
        (strcmp(o.outfilename.get(), "-") == 0))
    {
        if (o.split_pages)
        {
            usage("--split-pages may not be used when"
                  " writing to standard output");
        }
        if (o.verbose)
        {
            usage("--verbose may not be used when"
                  " writing to standard output");
        }
        if (o.progress)
        {
            usage("--progress may not be used when"
                  " writing to standard output");
        }
    }

    if ((! o.split_pages) &&
        QUtil::same_file(o.infilename.get(), o.outfilename.get()))
    {
        QTC::TC("qpdf", "qpdf same file error");
        usage("input file and output file are the same;"
              " use --replace-input to intentionally overwrite the input file");
    }
}

void
QPDFJob::initializeFromArgv(int argc, char* argv[], char const* progname_env)
{
    if (progname_env == nullptr)
    {
        progname_env = "QPDF_EXECUTABLE";
    }
    QPDFArgParser qap(argc, argv, progname_env);
    setMessagePrefix(qap.getProgname());
    ArgParser ap(qap, *this);
    ap.parseOptions();
}
