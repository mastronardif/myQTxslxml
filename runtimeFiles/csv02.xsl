<xsl:stylesheet
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:str="http://exslt.org/strings"
	extension-element-prefixes='str'
>
	<xsl:output method="xml" omit-xml-declaration="yes"/>

	<!-- break into rows -->
	<xsl:variable name='rows' select='str:split(root, "&#xA;")' />

	<!-- root - kick things off -->
	<xsl:template match='/'>
		<root>
			<xsl:apply-templates select='$rows' mode='row' />
		</root>
	</xsl:template>

	<!-- rows -->
	<xsl:template match='token' mode='row'>
		<xsl:variable name='cols' select='str:split(., ",")' />
		<row>
		<!--
			<xsl:apply-templates select='$cols' mode='col' />
			-->

<xsl:call-template name="output-tokens">
<xsl:with-param name="list"><xsl:apply-templates select='.' /></xsl:with-param>
<xsl:with-param name="delimiter">,</xsl:with-param>
</xsl:call-template>
		</row>
	</xsl:template>

	<!-- columns -->
	<xsl:template match='token' mode='col'>
		<xsl:element name='col{position()}'>
			<xsl:value-of select='.' />
		</xsl:element>
	</xsl:template>

<xsl:template name="output-tokens">
<xsl:param name="list"/>
<xsl:param name="delimiter"/>
<xsl:variable name="newlist">
<xsl:choose>
<xsl:when test="contains($list, $delimiter)">
<xsl:value-of select="normalize-space($list)"/>
</xsl:when>
<xsl:otherwise>
<xsl:value-of select="concat(normalize-space($list), $delimiter)"/>
</xsl:otherwise>
</xsl:choose>
</xsl:variable>
<xsl:variable name="first" select="substring-before($newlist, $delimiter)"/>
<xsl:variable name="remaining" select="substring-after($newlist, $delimiter)"/>
<num>
<xsl:value-of select="$first"/>
</num>

<xsl:if test="$remaining">
<xsl:call-template name="output-tokens">
<xsl:with-param name="list" select="$remaining"/>
<xsl:with-param name="delimiter">
<xsl:value-of select="$delimiter"/>
</xsl:with-param>
</xsl:call-template>
</xsl:if>
</xsl:template>

</xsl:stylesheet>