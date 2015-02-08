<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:csv="csv:csv">
<xsl:output method="text" encoding="utf-8" />
<xsl:strip-space elements="*" />

    <xsl:variable name="delimiter" select="','" />

<!--last Modified ______ 11:12AM
Purpose:  Used to ____ ,
-->

<xsl:template match="/">
 <xsl:for-each select="ssn">

    <xsl:if test="1 = 1">
        <xsl:text>&#xa;</xsl:text>

        <xsl:text>row,</xsl:text>
        <xsl:for-each select="./@*">
            <xsl:value-of select="name(.)"/><xsl:text>,</xsl:text>
        </xsl:for-each>
        <xsl:text>&#xa;</xsl:text>
    </xsl:if>

    <xsl:value-of select="position()"/> <xsl:text>,</xsl:text>
    <xsl:for-each select="./@*">
        <xsl:text>"</xsl:text><xsl:value-of select="."/><xsl:text>",</xsl:text>
    </xsl:for-each>

    </xsl:for-each>


<xsl:variable name="makeRespLs00">

 <xsl:for-each select="ssn/p/v">

    <xsl:if test="position() = 1">
        <xsl:text>&#xa;</xsl:text>
        <xsl:text>row,</xsl:text>
        <xsl:for-each select="./@*">
            <xsl:value-of select="name(.)"/><xsl:text>,</xsl:text>
        </xsl:for-each>
        <xsl:text>p_id,</xsl:text>
        <xsl:text>&#xa;</xsl:text>
    </xsl:if>

<xsl:value-of select="position()"/> <xsl:text>,</xsl:text>
 	<xsl:for-each select="./@*">
        <xsl:text>"</xsl:text><xsl:value-of select="."/><xsl:text>",</xsl:text>
    </xsl:for-each>
    <xsl:value-of select="count(../preceding-sibling::*)+1"/><xsl:text>",</xsl:text>

    <xsl:text>&#xa;</xsl:text>

 </xsl:for-each>

</xsl:variable>
<xsl:copy-of select="$makeRespLs00"/>

  </xsl:template>

</xsl:stylesheet>
