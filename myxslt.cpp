//namespace MyXslt
//{


#include <stdio.h>
#include <string.h>
#include <libxml/xmlmemory.h>
#include <libxml/debugXML.h>
#include <libxml/HTMLtree.h>
#include <libxml/xmlIO.h>
//#include <libxml/DOCBparser.h>
#include <libxml/xinclude.h>
#include <libxml/catalog.h>
#include <libxslt/xslt.h>
#include <libxslt/xsltInternals.h>
#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>

extern int xmlLoadExtDtdDefaultValue;
int my_xslt_main(const char *fnXslt, const char *theParamsArg, const char *fnSrcXml, const char *fnOut)
{
    const char *params[16 + 1];
    int nbparams = 0;
    xsltStylesheetPtr cur = NULL;
    xmlDocPtr doc, res;
    const char *ofile[1];  ofile[0]=NULL;
    int iRetval = 0; // default success.

    char *token;
    char theParams[80];
    strncpy(theParams, theParamsArg, sizeof(theParams)/sizeof(theParams[0]));
    const char del[2] = "-";
    token = strtok(theParams, del);
    int icount = 0;
    while( token != NULL )
    {
        // skip 1st token.
        if (icount != 0)
        {
            params[nbparams++] = token;
        }
        icount++;
          printf( "token (%s)\n", token );

          token = strtok(NULL, del);
    }
    params[nbparams] = NULL;

    xmlSubstituteEntitiesDefault(1);
    xmlLoadExtDtdDefaultValue = 1;
    cur = xsltParseStylesheetFile((const xmlChar *)fnXslt);
    doc = xmlParseFile(fnSrcXml);
    // Fm 4/10/14 res = xsltApplyStylesheet(cur, doc, params);
    // Fm 4/10/14 add error notification.
    {
        // FM when you get a chance get the error from stderr
        //xsltNewTransformContext()
        xsltTransformContextPtr ctxt = xsltNewTransformContext(cur, doc);
        res = xsltApplyStylesheetUser(cur, doc, params, NULL,
                             stderr, ctxt);
        if (!res || (ctxt->state == XSLT_STATE_ERROR) ||
               (ctxt->state == XSLT_STATE_STOPPED))
        {
            iRetval += -1;
        }
    }

    if(fnOut[0])
    {
        FILE *fp;
        fp=fopen(fnOut, "w+");
        if (fp)
        {
            if (!res)
            {
                iRetval += -2;   // error creating transform.
            }

            int fclose(FILE *a_file);
            xsltSaveResultToFile(fp, res, cur);

            fclose(fp);
        }
        else
        {
            printf("Error: fopen(%s)\n", fnOut);
        }
    }
    else
    {
        xsltSaveResultToFile(stdout, res, cur);
    }

    xsltFreeStylesheet(cur);
    xmlFreeDoc(res);
    xmlFreeDoc(doc);

        xsltCleanupGlobals();
        xmlCleanupParser();

    return(iRetval);

}

void usage(const char *name)
{
    printf("FM 105- Usage: %s [options -o outfile] stylesheet file [file ...]\n", name);
    printf("      --param name value : pass a (parameter,value) pair\n");

       /*
        *
     root_xl_worksheets_sheetN.xml.xsl
   a2Session_sheet1.xml
    -param QN "'5'"
    /Users/frank.mastronardi/fxm/dev/xml/myexcel/root_xl_worksheets_sheetN.xml.xsl
    /Users/frank.mastronardi/fxm/dev/xml/myexcel/a2Session_sheet1.xml
    /Users/frank.mastronardi/fxm/dev/xml/myexcel

   Z:\fxm\dev\xml\myexcel
   */
}

//}
