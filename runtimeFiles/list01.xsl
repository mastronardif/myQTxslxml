<xsl:stylesheet
version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform"

xmlns:my="http://www.w3.org/2005/Atom"
xmlns:gd="http://schemas.google.com/g/2005" 
	xmlns:media="http://search.yahoo.com/mrss/" 
	xmlns:openSearch="http://a9.com/-/spec/opensearchrss/1.0/" 
	xmlns:yt="http://gdata.youtube.com/schemas/2007"
>

<xsl:output method="xml" indent="yes"/>


<!--last Modified 7/01/14 9:47 PM
Purpose:  Used to create sheet 1 for report ___,
xsltproc  -o .\thelist.xml  .\list01.xsl  .\di_vidoes.xml
%MY_exe%  -o  %MY_outdir%\root_xl_worksheet_sheet1.xml  %MY_indir%\root_xl_worksheet_sheet1.xsl  %MY_indir%\%MY_DataXML%
-->

<!--
<xsl:key name='string' match='strings/string' use='@id' />
<xsl:variable name="strings" select="document('list02.xml')/strings"/>
-->
<xsl:template match="/">

<root>

    <xsl:for-each select="my:feed/my:entry">
<card>
	<!--
    	<xsl:value-of select="my:title" />
    	<img height="40px" width="40px" alt="wtf"> 
    -->
    
    <img  alt="wtf"> 
    	<xsl:attribute name="src">
    		<xsl:value-of select="media:group/media:thumbnail/@url" />
    </xsl:attribute>

</img>
 <br/>
<a> 
	    	<xsl:attribute name="href">
    		<xsl:value-of select="media:group/media:player/@url" />

    </xsl:attribute>
<xsl:value-of select="my:title" />
	</a>
    	<!-- <xsl:value-of select="media:group/media:player/@url" /> -->
    	<!--<xsl:value-of select="./media:group/media:thumbnail/*" />
    -->
</card>
<br/>
	</xsl:for-each>

</root>		
</xsl:template>

</xsl:stylesheet>
