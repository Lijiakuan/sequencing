/*  $Id: traversal_spec_file_parser.cpp 354091 2012-02-23 12:02:31Z kornbluh $
* ===========================================================================
*
*                            PUBLIC DOMAIN NOTICE
*               National Center for Biotechnology Information
*
*  This software/database is a "United States Government Work" under the
*  terms of the United States Copyright Act.  It was written as part of
*  the author's official duties as a United States Government employee and
*  thus cannot be copyrighted.  This software/database is freely available
*  to the public for use. The National Library of Medicine and the U.S.
*  Government have not placed any restriction on its use or reproduction.
*
*  Although all reasonable efforts have been taken to ensure the accuracy
*  and reliability of the software and data, the NLM and the U.S.
*  Government do not and cannot warrant the performance or results that
*  may be obtained by using this software or data. The NLM and the U.S.
*  Government disclaim all warranties, express or implied, including
*  warranties of performance, merchantability or fitness for any particular
*  purpose.
*
*  Please cite the author in any work or product based on this material.
*
* ===========================================================================
*
* Author: Michael Kornbluh
*
* File Description:
*   This generates many of the functions in newcleanup.cpp to reduce errors.
*/

/*
 ***** FORMAT OF SPECIFICATION FILE *****
 *
 * Comments are marked with '#', like in shell-scripts.
 * The first 3 clauses must be three lines like these:

output_header_file "C:/Users/kornbluh/Documents/toolkit/c++/include/objtools/cleanup/autogenerated_cleanup.hpp"

output_source_file "C:/Users/kornbluh/Documents/toolkit/c++/src/objtools/cleanup/autogenerated_cleanup.cpp"

output_class_name ncbi::objects::CAutogeneratedCleanup

 * They specify where to put the auto-generated header file and source file, and the name of the class that will contain
 * the auto-generated code, with complete namespace.  After this, there aren't restrictions on order and you can place clauses of any type in any order,
 * although you probably want to keep it organized somehow just for readability and cleanliness.
 * 
 * One type is the "member" clause.  This specifies extra members of the cleanup class, which are set in the constructor.
 * Example:

member { int m_Foo }

 * That example would cause the cleanup class to require an int parameter.
 *
 * Another kind of clause is a "root" clause.  This specifies the "root" objects which are used as the starting point
 * for traversals.  You also specify the name of the traversal functions.  Example:

root Seq-entry BasicCleanupSeqEntry

 * That example shows a case where we generate a public function called BasicCleanupSeqEntry which takes Seq-entry
 * objects (CSeq_entry in C++), and traverses down from there.  All helper functions are private.
 *
 * You can tell the auto-generator to a put a forward declaration in the header file.  Example:

header_forward_declaration CSomeClass

 * That clause will cause the line "class CSomeClass;" to appear in the header file.
 *
 * The auto-generator will try to include the class files needed.  However, if there are any that it skips for 
 * whatever reason, you can manually force it to add include lines to the generated header or source file.
 * Example:

header_include <objtools/cleanup/newcleanup.hpp>

source_include <objtools/cleanup/autogenerated_cleanup.hpp>
 
 * Here, it's also okay to use double-quotes instead of angle-brackets.
 *
 * Now, consider cases where you don't want to traverse down certain
 * fields.  Here's example syntax for that:

deprecated {
    Variation-ref.population-data ,
    Variation-ref.validated
}

 * In this case, no traversal functions will be generated 
 * for Variation-ref.population-data and below.
 *
 ********************************************************************************
 *
 * Finally, we get to the most interesting clause allowed: the "use" clause.  Here
 * is a simple example:

use m_NewCleanup.x_DateStdBC { Date-std }

 * This means: "anywhere that there's a Date-std object, regardless of how you got there,
 * call m_NewCleanup.x_DateStdBC to clean it up."  m_NewCleanup.x_DateStdBC should
 * take an argument of type "CDate_std &".  Here's a slightly more complex example:

use m_NewCleanup.x_ExpandCombinedQuals { Seq-feat.qual }

 * In this case, we call m_NewCleanup.x_ExpandCombinedQuals for any parts named "qual" which are under
 * any Seq-feat (This prevents us from calling it for quals like the one in, e.g., Medline-mesh.)
 *
 * By default, a node's user-defined functions are called and then children are traversed.  You can
 * override it by putting "POST" keyword before each pattern where you want the user function called
 * before the children nodes are traversed.  Example:

use m_NewCleanup.SeqfeatBC { POST Seq-feat }

 * Pre is the default so that any new elements created higher up will still be cleaned without
 * the need to explicitly call cleanup.  You may want to use POST when you want your children
 * cleaned up before you look at them (e.g. to make sure strings are cleaned, etc.)
 *
 * Patterns are basically of the same form as the "stack paths" which are documented elsewhere.
 * They are dot-separated units, each of which is either a type name (e.g. "Seq-loc" ) or a 
 * member name (e.g. "location"), or a "?", which means
 * "one of anything".  You can't have a question mark as the first or last part of a pattern.
 * Star ("*"), which would signify "one or more of anything", is NOT supported at this time 
 * for performance reasons, but might be in the future.
 *
 * Use "E" to specify each member of an array.  For example:

use m_NewCleanup.x_CleanupStringMarkChanged { User-field.data.strs.E }

 * This calls m_NewCleanup.x_CleanupStringMarkChanged for *each* member of the array.
 * This means you don't have to set up the for-loop to iterate through User-field.data.strs
 *
 * Look at this example:

use m_NewCleanup.ConvertSeqLocWholeToInt {

    Seq-loc EXCEPT { product }

}

 * Here, we call ConvertSeqLocWholeToInt for any Seq-loc as long as it's not called "product".
 * This is because whole locations are allowed for product and don't generally need conversion.
 * You can list multiple exceptions, separated by whitespace.
 *
 * You can have multiple patterns in one use clause.  Example:

use m_NewCleanup.x_CleanupStringMarkChanged {
    Seqdesc.name ,
    Seqdesc.title
    # and more...
}

 * You can have EXCEPT clauses or whatever for each part.
 *
 * Sometimes you want to pass a higher-up data piece.  Look at this example:

use m_NewCleanup.ProtFeatfBC { Seq-feat.data.prot AND Seq-feat }

 * Here, m_NewCleanup.ProtFeatfBC gets passed any prot which is inside the data
 * inside any Seq-feat object, AND it also gets a reference to the parent Seq-feat
 * itself.  In this case, m_NewCleanup.ProtFeatfBC must take two arguments:
 * "CProf_ref&" and "CSeq_feat&".
 * You can have as many arguments as you like, but the argument patterns
 * MUST be a strict prefix string of the original pattern.
 * For example, this would be illegal:

##### ILLEGAL SYNTAX
use m_NewCleanup.ProtFeatfBC { Seq-feat.data.prot AND ftable }
##### ILLEGAL SYNTAX

 * 
 * You can also specify syntax for "member macros" like CLEAN_STRING_MEMBER.  Example:

membermacro CLEAN_STRING_MEMBER {
    Gene-ref.locus
}

 * In appropriate places in the auto-generated code, you will have code like "CLEAN_STRING_MEMBER(arg0, Locus)"
 * where arg0 is actually the name of some variable that holds Gene-ref. 
 *
 * The files are basically whitespace-insensitive, relying on commas
 * and such to tell how to parse things.  New-lines
 * are treated exactly the same as any other whitespace, with the 
 * sole exception of handling comments.
 */

#include <ncbi_pch.hpp>
#include <corelib/ncbistre.hpp>

#include "traversal_spec_file_parser.hpp"
#include <iterator>

BEGIN_NCBI_SCOPE

int CTraversalSpecFileParser::CDescFileNode::ms_HighestID = 0;

CTraversalSpecFileParser::CDescFileNode::CDescFileNode( 
    const string &func, const string &pattern, 
    const std::vector<std::string> &except_patterns,
    const std::vector<std::string> &arg_patterns,
    const std::vector<std::string> &constant_args,
    EWhen when ) 
    : m_Func(func), m_ConstantArgs(constant_args), m_ID(++ms_HighestID), m_When(when)
{
    NStr::Tokenize( pattern, ".", m_Pattern );

    m_ExceptPatterns.resize( except_patterns.size() );
    int ii = 0;
    for( ; ii < (int)m_ExceptPatterns.size(); ++ii ) {
        NStr::Tokenize( except_patterns[ii], ".", m_ExceptPatterns[ii] );
    }

    m_ArgPatterns.resize( arg_patterns.size() );
    for( ; ii < (int)m_ArgPatterns.size(); ++ii ) {
        NStr::Tokenize( arg_patterns[ii], ".", m_ArgPatterns[ii] );
    }
}

string 
CTraversalSpecFileParser::CDescFileNode::ToString(void)
{
    CNcbiOstrstream result;

    result << "(id " << m_ID << ") use " << m_Func << " {" << endl;
    result << "  " << NStr::Join( m_Pattern, "." ) << endl;
    if( ! m_ExceptPatterns.empty() ) {
        result << "    EXCEPT {" << endl;
        ITERATE( TPatternVec, pattern_iter, m_ExceptPatterns ) {
            result << "      " << NStr::Join( *pattern_iter, "." ) << endl;
        }
        result << "    }" << endl;
    }
    ITERATE( TPatternVec, arg_iter, m_ArgPatterns ) {
        result << "    , " << NStr::Join( *arg_iter, "." ) << endl;
    }
    ITERATE( vector<string>, arg_iter, m_ConstantArgs ) {
        result << "    , CONSTANT \"" << *arg_iter << "\"" << endl;
    }
    result << "}" << endl;
    // Just in case it doesn't null-terminate
    result << '\0'; 

    return result.str();
}

void CTraversalSpecFileParser::CDescFileNode::ConvertToMemberMacro(void)
{
    // chop off the last part of the main pattern and convert it into a constant arg
    if( m_Pattern.size() < 2 ) {
        throw runtime_error("membermacros' patterns must have a dot (e.g. 'Gene-ref.locus' but NOT 'Gene-ref') ");
    }

    // set member_arg to be the last part of the pattern
    m_ConstantArgs.push_back(kEmptyStr);
    string &member_arg = m_ConstantArgs.back();
    member_arg.swap( m_Pattern.back() );
    m_Pattern.pop_back();

    // transform the member_arg to match how it should be used
    NStr::ReplaceInPlace( member_arg, "-", "_" );
    NStr::ToLower( member_arg );
    member_arg[0] = toupper(member_arg[0]);
}

bool CTraversalSpecFileParser::CTokenizer::GetNextNoThrow( string& out_next_token )
{
    out_next_token.clear();

    if( ! x_TryToGetTokensIfNone() ) {
        return false;
    }

    // return the token we found before
    out_next_token = m_NextTokens.front();
    m_NextTokens.pop_front();
    return true;
}

void CTraversalSpecFileParser::CTokenizer::GetNextOrThrow( string& out_next_token ) 
{
    if( ! GetNextNoThrow(out_next_token) ) {
        throw CNoMoreTokens();
    }
}

bool CTraversalSpecFileParser::CTokenizer::NextWillBe( const string& out_next_token ) 
{
    // refill m_NextTokens if empty
    if( ! x_TryToGetTokensIfNone() ) {
        throw CNoMoreTokens();
    }

    return ( m_NextTokens.front() == out_next_token );
}

void CTraversalSpecFileParser::CTokenizer::DiscardOne( const char* should_be )
{
    string next_token;
    GetNextOrThrow( next_token );
    if( (NULL != should_be) && (next_token != should_be) ) {
        throw CParseError( string("Got unexpected token: '") + next_token + "', expected: '" + should_be + "'" );
    }
}

void CTraversalSpecFileParser::CTokenizer::GetUntil( std::vector<std::string> &out_tokens, const string &expected_token )
{
    while( ! NextWillBe(expected_token) ) {
        out_tokens.push_back(kEmptyStr);
        GetNextOrThrow(out_tokens.back());
    }
    DiscardOne(expected_token.c_str());
}

bool CTraversalSpecFileParser::CTokenizer::x_TryToGetTokensIfNone(void)
{
    // symbols which are their own token
    static const char *kDelims = "{},<>";

    // if there are no more known tokens, read until there are
    while( m_NextTokens.empty() && m_Istream.good() ) {
        string next_word;
        m_Istream >> next_word;

        // if there's a string, we have to read until the end of the string
        if( next_word[0] == '\"' && next_word[next_word.length()-1] != '\"') {
            x_ReadUntil(next_word, '\"');
            next_word += '\"';
        }

        // if there's a comment, skip the rest of the line
        string::size_type comment_location = next_word.find_first_of( "#" );
        if( comment_location != string::npos ) {
            next_word.resize( comment_location );
            string ignored;
            x_ReadUntil(ignored, '\n');
        }

        // split the "word" into tokens
        string::size_type token_start = 0;
        while( token_start < next_word.length() ) {
            // token stops just before token_end
            string::size_type token_end = next_word.find_first_of( kDelims, token_start );
            if( token_end == string::npos ) {
                token_end = next_word.length();
            } else if( token_end == token_start ) {
                // first char is a delim
                ++token_end;
            }

            m_NextTokens.push_back(kEmptyStr);
            copy( next_word.begin() + token_start, next_word.begin() + token_end, back_inserter(m_NextTokens.back()) );

            token_start = token_end;
        }
    }

    return ! m_NextTokens.empty();
}

void CTraversalSpecFileParser::CTokenizer::x_ReadUntil( string &next_word, char last_char )
{
    m_Istream.setf( (ios::fmtflags)0, ios::skipws );

    char ch = '\0';
    while( m_Istream.good() ) {
        m_Istream >> ch;
        if( ch == last_char ) {
            break;
        }
        next_word += ch;
    }

    m_Istream.setf( ios::skipws, ios::skipws );
}

CTraversalSpecFileParser::CTraversalSpecFileParser( CNcbiIstream &istream )
: m_IsPruningAllowed(true), m_IsMergingAllowed(true)
{
    // autogenerated file always has a CScope argument
    m_Members.push_back( TMemberRef( new SMember("CScope &", "m_Scope") ) );

    // begin parsing
    CTokenizer tokenizer( istream );

    // "output_file_base" should be the first entry
    x_ParseOutputFiles( tokenizer );

    // "output_class_name" should be the next entry
    x_ParseOutputClassNameClause( tokenizer );

    // each iteration deals with one section like "use foo { ... }" and similar.
    string next_token;
    while( tokenizer.GetNextNoThrow(next_token) ) {
        if( next_token == "use" ) {
            x_ParseUseClause(tokenizer);
        } else if( next_token == "root" ) {
            x_ParseRootClause(tokenizer);
        } else if( next_token == "member" ) {
            x_ParseMemberClause(tokenizer);
        } else if( next_token == "header_forward_declaration" ) {
            x_ParseHeaderForwardDeclarationClause(tokenizer);
        } else if( next_token == "header_include" ) {
            x_ParseInclude( m_HeaderIncludes, tokenizer);
        } else if( next_token == "source_include" ) {
            x_ParseInclude( m_SourceIncludes, tokenizer);
        } else if( next_token == "no_pruning" ) {
            m_IsPruningAllowed = false;
        } else if( next_token == "no_merging" ) {
            m_IsMergingAllowed = false;
        } else if( next_token == "membermacro" ) {
            x_ParseMemberMacro(tokenizer);
        } else if( next_token == "deprecated" ) {
            x_ParseDeprecated(tokenizer);
        } else {
            throw CParseError( "Bad top-level token '" + next_token + "'");
        }
    }
}

void CTraversalSpecFileParser::x_ParseOutputFiles( CTokenizer &tokenizer )
{
    // little validation is done since a path can be pretty much any string

    tokenizer.DiscardOne("output_header_file");
    tokenizer.GetNextOrThrow( m_OutputFileHeader );
    // strip out the double-quotes
    m_OutputFileHeader = m_OutputFileHeader.substr(1, m_OutputFileHeader.length() - 2);
    
    tokenizer.DiscardOne("output_source_file");
    tokenizer.GetNextOrThrow( m_OutputFileSource );
    // strip out the double-quotes
    m_OutputFileSource = m_OutputFileSource.substr(1, m_OutputFileSource.length() - 2);
}

void CTraversalSpecFileParser::x_ParseOutputClassNameClause( CTokenizer &tokenizer )
{
    tokenizer.DiscardOne("output_class_name");
    string output_class_name_with_namespace;
    tokenizer.GetNextOrThrow( output_class_name_with_namespace );

    NStr::Tokenize( output_class_name_with_namespace, "::", m_Namespace );

    // last piece becomes class-name, though
    m_OutputClassName = m_Namespace.back();
    m_Namespace.pop_back();

    // make sure the output class name matches the 
    // regular expression pattern "C[A-Za-z_]+"
    if( m_OutputClassName[0] != 'C' ) {
        throw CParseError( "illegal output_class_name: \"" + m_OutputClassName + "\"" );
    }
    ITERATE( string, char_iter, m_OutputClassName ) {
        if( ! isalpha(*char_iter) && *char_iter != '_' ) {
            throw CParseError( "illegal output_class_name: \"" + m_OutputClassName + "\"" );
        }
    }    
}

void CTraversalSpecFileParser::x_ParseUseClause( CTokenizer &tokenizer )
{
    string func_name;
    tokenizer.GetNextOrThrow( func_name );

    tokenizer.DiscardOne( "{" );

    while( ! tokenizer.NextWillBe("}") ) {

        CDescFileNode::EWhen when = CDescFileNode::eWhen_beforeCallees;
        if( tokenizer.NextWillBe("POST") ) {
            tokenizer.DiscardOne("POST");
            when = CDescFileNode::eWhen_afterCallees;
        }

        string pattern;
        tokenizer.GetNextOrThrow( pattern );

        if( ! x_IsValidPattern(pattern) ) {
            throw CParseError("This is not a valid pattern: '" + pattern + "'");
        }

        vector<string> except_patterns;
        if( tokenizer.NextWillBe("EXCEPT") ) {
            x_ParseUseExceptClause( tokenizer, except_patterns );
        }

        vector<string> arg_patterns;
        if( tokenizer.NextWillBe("AND") ) {
            x_ParseUseArgClause( tokenizer, pattern, arg_patterns );
        }

        m_DescFileNodes.push_back( CRef<CDescFileNode>(new CDescFileNode( func_name, pattern, except_patterns, arg_patterns, vector<string>(), when )) );

        if( tokenizer.NextWillBe(",") ) {
            tokenizer.DiscardOne(",");
        } else {
            break;
        }
    };

    tokenizer.DiscardOne("}");
}

void CTraversalSpecFileParser::x_ParseUseExceptClause( 
    CTokenizer &tokenizer, 
    std::vector<std::string> &out_except_patterns )
{
    tokenizer.DiscardOne("EXCEPT");
    tokenizer.DiscardOne("{");

    while( ! tokenizer.NextWillBe("}") ) {
        out_except_patterns.push_back(kEmptyStr);
        string &except_pattern = out_except_patterns.back();

        tokenizer.GetNextOrThrow(except_pattern);
        if( ! x_IsValidPattern(except_pattern) ) {
            throw CParseError("This is not a valid pattern: '" + except_pattern + "'");
        }

        if( tokenizer.NextWillBe(",") ) {
            tokenizer.DiscardOne(",");
        } else {
            break;
        }
    }

    tokenizer.DiscardOne("}");
}

void CTraversalSpecFileParser::x_ParseUseArgClause( CTokenizer &tokenizer, 
    const string &main_pattern,
    std::vector<std::string> &out_arg_patterns )
{
    while( tokenizer.NextWillBe("AND") ) {
        tokenizer.DiscardOne("AND");

        out_arg_patterns.push_back(kEmptyStr);
        string &arg_pattern = out_arg_patterns.back();

        tokenizer.GetNextOrThrow(arg_pattern);
        if( ! x_IsValidPattern(arg_pattern) ) {
            throw CParseError("This is not a valid pattern: '" + arg_pattern + "'");
        }

        if( ( arg_pattern.empty() ) ||
            (! NStr::StartsWith( main_pattern, arg_pattern ) ) ||
            ( main_pattern == arg_pattern ) ||
            ( main_pattern[arg_pattern.length()] != '.' ) )
        {
            throw CParseError("Arg patterns must be a prefix of the main pattern.  main_pattern: '" + 
                main_pattern + "', arg pattern: '" + arg_pattern + "'");
        }
    }
}

void CTraversalSpecFileParser::x_ParseRootClause( CTokenizer &tokenizer )
{
    // root type
    string root_type;
    tokenizer.GetNextOrThrow( root_type );

    // root func
    string root_func;
    tokenizer.GetNextOrThrow( root_func );

    // looks good, so add it
    m_RootTypes.push_back( TRootInfoRef(new SRootInfo(root_type, root_func)) );
}

void CTraversalSpecFileParser::x_ParseMemberClause( CTokenizer &tokenizer )
{
    tokenizer.DiscardOne("{");
    vector<string> parts;
    tokenizer.GetUntil(parts, "}");

    if( parts.size() < 2 ) {
        throw CParseError("bad member.  specify type, then variable name");
    }

    // extract variable name
    const string variable_name = parts.back();
    parts.pop_back();

    if( (variable_name.length() < 4) || (! NStr::StartsWith(variable_name, "m_") ) ) {
        throw CParseError("member variable must start with m_ and be at least 4 characters.  You gave: \"" + variable_name + "\"");
    }

    // The rest is the type name
    string type_name = NStr::Join( parts, " " );

    m_Members.push_back( TMemberRef( new SMember(type_name, variable_name) ) );
}

void CTraversalSpecFileParser::x_ParseInclude( std::vector< std::string > &include_list, CTokenizer &tokenizer )
{
    string token;
    tokenizer.GetNextOrThrow(token);

    string result;
    if( token == "<" ) {
        string main_file_name;
        tokenizer.GetNextOrThrow(main_file_name);
        tokenizer.DiscardOne(">");
        include_list.push_back( "<" + main_file_name + ">" );
    } else if( token[0] == '\"' && token[token.length()-1] == '\"' ) {
        include_list.push_back( token );
    } else {
        throw CParseError( "Unparseable source_include: " + token );
    }
}

void CTraversalSpecFileParser::x_ParseHeaderForwardDeclarationClause( CTokenizer &tokenizer )
{
    m_HeaderForwardDeclarations.push_back(kEmptyStr);
    string &next_token = m_HeaderForwardDeclarations.back();
    tokenizer.GetNextOrThrow( next_token );
}

void CTraversalSpecFileParser::x_ParseMemberMacro( CTokenizer &tokenizer )
{
    // membermacro parses similar to "use" clauses, so we use the use-clause
    // parser and then just adjust its output.

    const int old_desc_file_nodes = m_DescFileNodes.size();
    x_ParseUseClause(tokenizer);

    std::vector< CRef<CDescFileNode> >::iterator desc_node_iter = m_DescFileNodes.begin();
    desc_node_iter += old_desc_file_nodes;
    for( ; desc_node_iter != m_DescFileNodes.end(); ++desc_node_iter ) {
        CDescFileNode &file_node = **desc_node_iter;
        
        file_node.ConvertToMemberMacro();
    }
}

void CTraversalSpecFileParser::x_ParseDeprecated( CTokenizer &tokenizer )
{
    tokenizer.DiscardOne( "{" );

    while( ! tokenizer.NextWillBe("}") ) {
        string pattern_str;
        tokenizer.GetNextOrThrow( pattern_str );

        if( ! x_IsValidPattern(pattern_str) ) {
            throw CParseError("This is not a valid pattern: '" + pattern_str + "'");
        }

        TPattern pattern;
        NStr::Tokenize( pattern_str, ".", pattern );

        m_DeprecatedPatterns.push_back( pattern );

        if( tokenizer.NextWillBe(",") ) {
            tokenizer.DiscardOne(",");
        } else {
            break;
        }
    }

    tokenizer.DiscardOne("}");
}

bool CTraversalSpecFileParser::x_IsValidPattern( const std::string & pattern )
{
    if( pattern.empty() ) {
        return false;
    }

    // pattern can't begin or end with wildcards
    if( pattern[0] == '?' || pattern[pattern.length()-1] == '?' ) {
        return false;
    }

    // pattern should be of the form where each period-separated
    // piece is either a wildcard ("?") or of the regular expression form "[A-Za-z-]+", but
    // the first and last can't be wildcards.
    string::const_iterator start_of_piece = pattern.begin();
    while( start_of_piece != pattern.end() ) {
        string::const_iterator end_of_piece = find( start_of_piece, pattern.end(), '.' );
        if( start_of_piece == end_of_piece ) {
            // empty piece
            return false;
        }
        if( *start_of_piece == '?' && (start_of_piece+1) == end_of_piece ) {
            // This part is okay; it's a wildcard. Do nothing.
        } else {
            // iterate through piece looking for bad chars
            string::const_iterator char_iter = start_of_piece;
            for( ; char_iter != end_of_piece; ++char_iter ) {
                if( ! isalpha(*char_iter) && *char_iter != '-' && *char_iter != ':' ) {
                    return false;
                }
            }
        }
        start_of_piece = ( (end_of_piece == pattern.end()) ? end_of_piece : 1 + end_of_piece );
    }
    
    // no problems found
    return true;
}

END_NCBI_SCOPE
