#include <qpdf/QPDFJob.hh>

// See "HOW TO ADD A COMMAND-LINE ARGUMENT" in README-maintainer.

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <cstdio>
#include <ctype.h>
#include <memory>
#include <sstream>

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
        ArgParser(QPDFArgParser& ap,
                  std::shared_ptr<QPDFJob::Config> c_main, QPDFJob& o);
        void parseOptions();

      private:
#       include <qpdf/auto_job_decl.hh>

        void usage(std::string const& message);
        void initOptionTables();

        QPDFArgParser ap;
        std::shared_ptr<QPDFJob::Config> c_main;
        std::shared_ptr<QPDFJob::CopyAttConfig> c_copy_att;
        std::shared_ptr<QPDFJob::AttConfig> c_att;
        std::shared_ptr<QPDFJob::PagesConfig> c_pages;
        std::shared_ptr<QPDFJob::UOConfig> c_uo;
        std::shared_ptr<QPDFJob::EncConfig> c_enc;
        std::vector<char*> accumulated_args; // points to member in ap
        char* pages_password;
        bool gave_input;
        bool gave_output;
    };
}

ArgParser::ArgParser(QPDFArgParser& ap,
                     std::shared_ptr<QPDFJob::Config> c_main, QPDFJob& o) :
    ap(ap),
    c_main(c_main),
    pages_password(nullptr),
    gave_input(false),
    gave_output(false)
{
    initOptionTables();
}

#include <qpdf/auto_job_help.hh>

void
ArgParser::initOptionTables()
{

#   include <qpdf/auto_job_init.hh>
    // add_help is defined in auto_job_help.hh
    add_help(this->ap);
}

void
ArgParser::argPositional(char* arg)
{
    if (! this->gave_input)
    {
        c_main->inputFile(arg);
        this->gave_input = true;
    }
    else if (! this->gave_output)
    {
        c_main->outputFile(arg);
        this->gave_output = true;
    }
    else
    {
        usage(std::string("unknown argument ") + arg);
    }
}

void
ArgParser::argEmpty()
{
    c_main->emptyInput();
    this->gave_input = true;
}

void
ArgParser::argReplaceInput()
{
    c_main->replaceInput();
    this->gave_output = true;
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
        << QPDFJob::json_out_schema_v1()
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
    std::string user_password = this->accumulated_args.at(0);
    std::string owner_password = this->accumulated_args.at(1);
    std::string len_str = this->accumulated_args.at(2);
    int keylen = 0;
    if (len_str == "40")
    {
        keylen = 40;
        this->ap.selectOptionTable(O_40_BIT_ENCRYPTION);
    }
    else if (len_str == "128")
    {
        keylen = 128;
        this->ap.selectOptionTable(O_128_BIT_ENCRYPTION);
    }
    else if (len_str == "256")
    {
        keylen = 256;
        this->ap.selectOptionTable(O_256_BIT_ENCRYPTION);
    }
    else
    {
        usage("encryption key length must be 40, 128, or 256");
    }
    this->c_enc = c_main->encrypt(keylen, user_password, owner_password);
}

void
ArgParser::argPages()
{
    this->accumulated_args.clear();
    this->c_pages = c_main->pages();
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
            QUtil::parse_numrange(range, 0);
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
    this->c_pages->pageSpec(file, range, this->pages_password);
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
    c_pages->endPages();
    c_pages = nullptr;
}

void
ArgParser::argUnderlay()
{
    this->c_uo = c_main->underlay();
    this->ap.selectOptionTable(O_UNDERLAY_OVERLAY);
}

void
ArgParser::argOverlay()
{
    this->c_uo = c_main->overlay();
    this->ap.selectOptionTable(O_UNDERLAY_OVERLAY);
}

void
ArgParser::argAddAttachment()
{
    this->c_att = c_main->addAttachment();
    this->ap.selectOptionTable(O_ATTACHMENT);
}

void
ArgParser::argCopyAttachmentsFrom()
{
    this->c_copy_att = c_main->copyAttachmentsFrom();
    this->ap.selectOptionTable(O_COPY_ATTACHMENT);
}

void
ArgParser::argEndEncryption()
{
    c_enc->endEncrypt();
    c_enc = nullptr;
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
    c_uo->path(arg);
}

void
ArgParser::argEndUnderlayOverlay()
{
    c_uo->endUnderlayOverlay();
    c_uo = nullptr;
}

void
ArgParser::argAttPositional(char* arg)
{
    c_att->path(arg);
}

void
ArgParser::argEndAttachment()
{
    c_att->endAddAttachment();
    c_att = nullptr;
}

void
ArgParser::argCopyAttPositional(char* arg)
{
    c_copy_att->path(arg);
}

void
ArgParser::argEndCopyAttachment()
{
    c_copy_att->endCopyAttachmentsFrom();
    c_copy_att = nullptr;
}

void
ArgParser::argJobJsonHelp()
{
    std::cout << QPDFJob::json_job_schema_v1() << std::endl;
}

void
ArgParser::usage(std::string const& message)
{
    this->ap.usage(message);
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
QPDFJob::initializeFromArgv(int argc, char* argv[], char const* progname_env)
{
    if (progname_env == nullptr)
    {
        progname_env = "QPDF_EXECUTABLE";
    }
    QPDFArgParser qap(argc, argv, progname_env);
    setMessagePrefix(qap.getProgname());
    ArgParser ap(qap, config(), *this);
    qap.addFinalCheck(
        QPDFArgParser::bindBare(&QPDFJob::checkConfiguration, this));
    ap.parseOptions();
}
